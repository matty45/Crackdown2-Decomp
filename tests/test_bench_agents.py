"""The benchmark's agents and runner under a shared rate limit: the request pacer keeps every process under the limit,
a 429 is waited out (and a task that waits too long is not scored), a matrix runs task by task and skips a model that
keeps failing, a timed-out agent's whole process tree is killed, and the Kilo preset refuses a configuration that is
not its sandbox. No game executable or XDK is needed."""
import http.server
import json
import os
import pathlib
import subprocess
import sys
import tempfile
import threading
import time
import unittest
from unittest import mock

TOOLS = pathlib.Path(__file__).resolve().parents[1] / 'tools'
sys.path.insert(0, str(TOOLS))
import bench  # noqa: E402
import bench_chat  # noqa: E402
import bench_kilo  # noqa: E402
import cd2  # noqa: E402


def write(path, data):
    with open(path, 'w') as f:
        json.dump(data, f)


class Clock:
    """A fake clock whose sleep advances it."""

    def __init__(self, t=1000000.0):
        self.t, self.slept = t, []

    def now(self):
        return self.t

    def sleep(self, s):
        self.slept.append(s)
        self.t += s


class PacerTests(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.TemporaryDirectory()
        self.log = os.path.join(self.dir.name, 'llm_requests.jsonl')
        self.env = mock.patch.dict(os.environ, CD2_LLM_RATE_LOG=self.log)
        self.env.start()

    def tearDown(self):
        self.env.stop()
        self.dir.cleanup()

    def requests(self):
        with open(self.log, encoding='utf-8') as f:
            return [json.loads(line) for line in f if '"request"' in line]

    def test_requests_under_the_limit_do_not_wait(self):
        c = Clock()
        for _ in range(3):
            self.assertEqual(bench_chat.reserve('m', 3, now=c.now, sleep=c.sleep), 0.0)
        self.assertEqual(len(self.requests()), 3)
        self.assertEqual(c.slept, [])

    def test_a_full_window_waits_for_its_oldest_request(self):
        c = Clock()
        for _ in range(3):
            bench_chat.reserve('m', 3, now=c.now, sleep=c.sleep)
            c.t += 100
        start = c.t  # the requests were at start-300, start-200, start-100
        waited = bench_chat.reserve('m', 3, now=c.now, sleep=c.sleep)
        self.assertAlmostEqual(waited, 3600 - 300)
        self.assertAlmostEqual(c.t, start + 3600 - 300)
        self.assertEqual(len(self.requests()), 4)

    def test_no_limit_still_logs(self):
        c = Clock()
        bench_chat.reserve('m', None, now=c.now, sleep=c.sleep)
        self.assertEqual(len(self.requests()), 1)

    def test_two_processes_share_one_log(self):
        code = ('import sys; sys.path.insert(0, %r); import bench_chat\n'
                'for _ in range(20): bench_chat.reserve("m", 1000)\n') % str(TOOLS)
        ps = [subprocess.Popen([sys.executable, '-I', '-c', code], env=dict(os.environ, CD2_LLM_RATE_LOG=self.log))
              for _ in range(2)]
        for p in ps:
            self.assertEqual(p.wait(timeout=120), 0)
        rs = self.requests()  # every line whole: none interleaved
        self.assertEqual(len(rs), 40)
        self.assertEqual(len({r['pid'] for r in rs}), 2)


class RetryDelayTests(unittest.TestCase):
    def test_headers(self):
        now = lambda: 1700000000.0  # noqa: E731
        self.assertEqual(bench_chat.retry_delay({'Retry-After': '7'}, now), 7.0)
        self.assertEqual(bench_chat.retry_delay({'Retry-After': 'Tue, 14 Nov 2023 22:13:30 GMT'}, now), 10.0)
        self.assertEqual(bench_chat.retry_delay({'X-RateLimit-Reset': '1700000030'}, now), 30.0)
        self.assertEqual(bench_chat.retry_delay({'X-RateLimit-Reset': '1700000040000'}, now), 40.0)
        self.assertEqual(bench_chat.retry_delay({'X-RateLimit-Reset': '50'}, now), 50.0)
        self.assertIsNone(bench_chat.retry_delay({}, now))


class Gateway:
    """A local chat API: the first `refuse` requests get HTTP 429 (with Retry-After when given), the next `broken` a 200
    response with an error and no completion, then an answer."""

    def __init__(self, refuse, retry_after=None, broken=0):
        state = dict(n=0)

        class Handler(http.server.BaseHTTPRequestHandler):
            def log_message(self, *args):
                pass

            def do_POST(self):
                self.rfile.read(int(self.headers['Content-Length']))
                state['n'] += 1
                if state['n'] <= refuse:
                    self.send_response(429)
                    if retry_after is not None:
                        self.send_header('Retry-After', str(retry_after))
                    self.send_header('Content-Length', '0')
                    self.end_headers()
                    return
                if state['n'] <= refuse + broken:
                    out = json.dumps(dict(error=dict(message='Provider returned error', code=502))).encode()
                    self.send_response(200)
                    self.send_header('Content-Length', str(len(out)))
                    self.end_headers()
                    self.wfile.write(out)
                    return
                out = json.dumps(dict(choices=[dict(message=dict(content='STOP'))],
                                      usage=dict(prompt_tokens=3, completion_tokens=1, cost=0))).encode()
                self.send_response(200)
                self.send_header('Content-Type', 'application/json')
                self.send_header('Content-Length', str(len(out)))
                self.end_headers()
                self.wfile.write(out)

        self.state = state
        self.server = http.server.ThreadingHTTPServer(('127.0.0.1', 0), Handler)
        threading.Thread(target=self.server.serve_forever, daemon=True).start()
        self.url = 'http://127.0.0.1:%d/v1' % self.server.server_address[1]

    def close(self):
        self.server.shutdown()


class RateLimitTests(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.TemporaryDirectory()
        self.log = os.path.join(self.dir.name, 'llm_requests.jsonl')

    def tearDown(self):
        self.dir.cleanup()

    def call(self, gw, **env):
        c = Clock()
        with mock.patch.dict(os.environ, dict(CD2_LLM_BASE_URL=gw.url, CD2_LLM_RATE_LOG=self.log, **env)):
            for k in ('CD2_LLM_API_KEY', 'CD2_LLM_OPTIONS', 'CD2_LLM_RATE_PER_HOUR'):
                os.environ.pop(k, None)
            try:
                return bench_chat.api([dict(role='user', content='x')], 'm', sleep=c.sleep), c
            finally:
                gw.close()

    def events(self, kind):
        with open(self.log, encoding='utf-8') as f:
            return [json.loads(line) for line in f if '"%s"' % kind in line]

    def test_retry_after_is_honoured(self):
        (content, usage, waited, _), c = self.call(Gateway(2, retry_after=7))
        self.assertEqual(content, 'STOP')
        self.assertEqual(c.slept, [7.0, 7.0])
        self.assertEqual(waited, 14.0)
        self.assertEqual(usage['cost'], 0)
        self.assertEqual(len(self.events('429')), 2)
        self.assertEqual(len(self.events('request')), 3)

    def test_without_retry_after_it_backs_off(self):
        (content, _, waited, _), c = self.call(Gateway(2))
        self.assertEqual(c.slept, [60, 120])
        self.assertEqual(waited, 180)

    def test_an_error_in_a_200_response_is_retried(self):
        with mock.patch('sys.stdout'):
            (content, _, _, _), c = self.call(Gateway(0, broken=2))
        self.assertEqual(content, 'STOP')
        self.assertEqual(c.slept, [10, 20])

    def test_waiting_too_long_gives_up(self):
        with self.assertRaises(bench_chat.RateLimited):
            self.call(Gateway(5, retry_after=7), CD2_LLM_MAX_WAIT='10')

    def test_a_rate_limited_task_is_not_scored_and_runs_again(self):
        with mock.patch.object(bench, 'BENCH', self.dir.name):
            rec = dict(address='0x82000000', file='a.cpp', agent_exit=bench_chat.RATE_LIMITED, attempts=2,
                       rate_limited='rate limited (HTTP 429)')
            self.assertTrue(bench.agent_failed(rec))
            rp = bench.result_path(0x82000000, 'm')
            os.makedirs(os.path.dirname(rp))
            write(rp, rec)
            self.assertTrue(bench.needs_run(0x82000000, 'm'))
            rec.pop('rate_limited')
            rec['agent_exit'] = 0
            write(rp, rec)
            self.assertFalse(bench.needs_run(0x82000000, 'm'))


class ProtocolTests(unittest.TestCase):
    """Replies as free models really sent them (2026-11-20 smoke run): READ wrapped in their own tool-call markup."""

    def test_read_lines(self):
        self.assertEqual(bench_chat.requested_paths('READ include/a.h\nREAD docs/matching-notes.md\n'),
                         ['include/a.h', 'docs/matching-notes.md'])

    def test_read_inside_tool_call_markup(self):
        dots = ('<dots_function_call>\n<invokeinvoke name name="tool_call">\n<invokeparameter name="command">READ '
                'include/VEHICLE_CONTROL/cHelicopterController.h</parameter>\n</invoke>\n</dots_function_call>')
        ling = ('<tool_call>READ\n<arg_key>path</arg_key>\n<arg_value>include/VEHICLE_CONTROL/cHelicopterController.h'
                '</arg_value>\n</tool_call>\n<tool_call>READ\n<arg_key>path</arg_key>\n<arg_value>docs/matching-notes.md'
                '</arg_value>\n</tool_call>')
        self.assertEqual(bench_chat.requested_paths(dots), ['include/VEHICLE_CONTROL/cHelicopterController.h'])
        self.assertEqual(bench_chat.requested_paths(ling),
                         ['include/VEHICLE_CONTROL/cHelicopterController.h', 'docs/matching-notes.md'])

    def test_read_inside_a_tag(self):
        lfm = '<tool_call>\n<function=READ docs/matching-notes.md>\n</parameter>\n</function>\n</tool_call>'
        self.assertEqual(bench_chat.requested_paths(lfm), ['docs/matching-notes.md'])

    def test_read_lines_in_a_code_block_are_not_a_body(self):
        reply = '```markdown\nREAD include/VEHICLE_CONTROL/cHelicopterController.h\n```'
        self.assertIsNone(bench_chat.body_of(reply, 'GetSpeedLimit'))
        self.assertEqual(bench_chat.requested_paths(reply), ['include/VEHICLE_CONTROL/cHelicopterController.h'])
        self.assertIsNone(bench_chat.body_of('```\nREAD include/a.h\n```', 'f'))
        self.assertIn('return m_fSpeed;', bench_chat.body_of('```cpp\nreturn m_fSpeed;\n```', 'f'))
        self.assertIn('return m_fSpeed;', bench_chat.body_of('```\nreturn m_fSpeed;\n```', 'f'))

    def test_read_in_other_dialects(self):
        for reply, want in (
                ('<invoke name="read"><parameter name="path">include/AI/a.h</parameter></invoke>', ['include/AI/a.h']),
                ('<Read"> <parameter name="file_path">include/AI/a.h</parameter> </invoke>', ['include/AI/a.h']),
                ('<arg key=READ path=TASK.md></arg>', ['TASK.md']),
                ('<function=READ include/Equip/a.h </parameter> </function>', ['include/Equip/a.h'])):
            self.assertEqual(bench_chat.requested_paths(reply), want)

    def test_grep(self):
        with tempfile.TemporaryDirectory() as ws:
            os.makedirs(os.path.join(ws, 'include', 'AI'))
            with open(os.path.join(ws, 'include', 'AI', 'a.h'), 'w') as f:
                f.write('class cA {\n    float RetClassName() const;\n};\n')
            self.assertEqual(bench_chat.grep(ws, r'RetClass\w+'), 'include/AI/a.h:2:     float RetClassName() const;')
            self.assertIn('include/AI/a.h:2:', bench_chat.grep(ws, 'RetClassName()', 'include'))  # not a regex: text
            self.assertEqual(bench_chat.grep(ws, 'nothing here'), 'no match')
            self.assertIn('refused', bench_chat.grep(ws, 'x', '..'))

    def test_prose_is_not_a_request(self):
        self.assertEqual(bench_chat.requested_paths('I will READ the header first.\nSTOP'), [])

    def test_structured_tool_calls(self):
        read = dict(content=None, tool_calls=[dict(function=dict(name='read_file', arguments='{"path": "include/x.h"}'))])
        self.assertEqual(bench_chat.requested_paths(bench_chat.reply_text(read)), ['include/x.h'])
        other = dict(content='', tool_calls=[dict(function=dict(name='compile', arguments='{"code": "return 0;"}'))])
        self.assertIn('compile', bench_chat.reply_text(other))
        with mock.patch('sys.stdout'):
            self.assertEqual(bench_chat.reply_text(dict(content='', reasoning='...')), '')


class MatrixTests(unittest.TestCase):
    tasks = [dict(address='0x8200000%d' % i, tier=1) for i in range(5)]

    def test_parse(self):
        with tempfile.TemporaryDirectory() as d:
            p = os.path.join(d, 'm.txt')
            open(p, 'w').write('# free models\n\na-chat chat:vendor/a:free\nb-chat   chat:b\n')
            runs = cd2.bench_matrix(p)
            self.assertEqual([m for _, m in runs], ['a-chat', 'b-chat'])
            self.assertIn('bench_chat.py', runs[0][0])
            self.assertTrue(runs[0][0].endswith(' vendor/a:free'))
            open(p, 'w').write('a chat:x\na chat:y\n')
            with self.assertRaises(cd2.Fail):
                cd2.bench_matrix(p)
            open(p, 'w').write('lonely\n')
            with self.assertRaises(cd2.Fail):
                cd2.bench_matrix(p)

    def test_agent_options(self):
        self.assertTrue(cd2.bench_agent('chat:reflection/beam-free --tools').endswith(' reflection/beam-free --tools'))
        self.assertTrue(cd2.bench_agent('chat:m --tools --rounds 3').endswith(' m --tools --rounds 3'))
        self.assertEqual(cd2.bench_agent('aider --yes {task}'), 'aider --yes {task}')

    def test_task_major(self):
        jobs = [(t, m) for m in ('a', 'b', 'c') for t in self.tasks]  # built model by model
        got = [(j[0]['address'][-1], j[1]) for j in cd2.task_major(jobs, self.tasks)]
        self.assertEqual(got[:6], [('0', 'a'), ('0', 'b'), ('0', 'c'), ('1', 'a'), ('1', 'b'), ('1', 'c')])

    def test_a_failing_model_is_skipped(self):
        jobs = cd2.task_major([(t, m) for m in ('good', 'bad') for t in self.tasks], self.tasks)
        ran = []

        def one(job):
            ran.append(job[1])
            return dict(model=job[1], address=job[0]['address']), job[1] == 'bad'
        with mock.patch('sys.stderr'):
            rows, skipped = cd2.run_bench_jobs(jobs, one, 1)
        self.assertEqual(skipped, ['bad'])
        self.assertEqual(ran.count('good'), 5)
        self.assertEqual(ran.count('bad'), 3)
        self.assertEqual(len(rows), 8)

    def test_a_rate_limited_model_cools_down_while_others_go_on(self):
        jobs = cd2.task_major([(t, m) for m in ('fast', 'slow') for t in self.tasks[:3]], self.tasks)
        ran, limited = [], set()

        def one(job):
            key = (job[1], job[0]['address'])
            ran.append(key)
            first = job[1] == 'slow' and key not in limited  # each slow task is refused once
            limited.add(key)
            return dict(model=job[1], address=job[0]['address'], rate_limited=first), first
        with mock.patch('sys.stderr'):
            rows, skipped = cd2.run_bench_jobs(jobs, one, 1, cooldown=0.3)
        self.assertEqual(skipped, [])
        self.assertEqual(len(rows), 6)
        self.assertFalse(any(r['rate_limited'] for r in rows))
        a = lambda i: self.tasks[i]['address']  # noqa: E731
        # slow's first task is refused, so fast goes on with its tasks while slow cools down
        self.assertEqual(ran[:4], [('fast', a(0)), ('slow', a(0)), ('fast', a(1)), ('fast', a(2))])
        self.assertEqual(sorted(ran).count(('slow', a(1))), 2)


class ProcessTreeTests(unittest.TestCase):
    def alive(self, pid):
        if os.name == 'nt':
            out = subprocess.run(['tasklist', '/FI', 'PID eq %d' % pid, '/NH'], capture_output=True, text=True).stdout
            return str(pid) in out
        try:
            os.kill(pid, 0)
        except ProcessLookupError:
            return False
        return True

    def test_timeout_kills_the_grandchild(self):
        with tempfile.TemporaryDirectory() as d:
            pidfile = os.path.join(d, 'pid')
            code = ('import subprocess, sys, time; p = subprocess.Popen([sys.executable, "-c", "import time; '
                    'time.sleep(120)"]); open(%r, "w").write(str(p.pid)); time.sleep(120)') % pidfile
            t0 = time.time()
            got = bench.run_tree('"%s" -I -c "%s"' % (sys.executable, code.replace('"', '\\"')), 5,
                                 stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            self.assertEqual(got, 'timeout')
            self.assertLess(time.time() - t0, 60)
            with open(pidfile) as f:
                pid = int(f.read())
            for _ in range(20):
                if not self.alive(pid):
                    break
                time.sleep(0.5)
            self.assertFalse(self.alive(pid))

    def test_exit_status(self):
        self.assertEqual(bench.run_tree('"%s" -I -c "import sys; sys.exit(3)"' % sys.executable, 60), 3)


class KiloGuardTests(unittest.TestCase):
    check = 'py -I cd2.py bench check 0x82000000 --model m'

    def config(self, **changes):
        c = dict(model='kilo/x', permission=bench_kilo.rules(self.check), mcp={'ida': dict(enabled=False)})
        c.update(changes)
        return c

    def test_the_sandbox_passes(self):
        self.assertEqual(bench_kilo.config_problems(self.config(), self.check, 'kilo/x'), [])
        self.assertEqual(bench_kilo.config_problems(self.config(mcp=None), self.check, 'kilo/x'), [])

    def test_an_enabled_mcp_server_is_refused(self):
        for server in (dict(type='remote', url='https://mcp.deepwiki.com/mcp', enabled=True),
                       dict(type='remote', url='http://127.0.0.1:23343/mcp')):  # enabled unless it says otherwise
            problems = bench_kilo.config_problems(self.config(mcp={'deepwiki': server}), self.check, 'kilo/x')
            self.assertEqual(problems, ['MCP server deepwiki is enabled'])

    def test_other_rules_or_model_are_refused(self):
        rules = dict(bench_kilo.rules(self.check), bash='allow')
        self.assertEqual(len(bench_kilo.config_problems(self.config(permission=rules), self.check, 'kilo/x')), 1)
        self.assertEqual(len(bench_kilo.config_problems(self.config(), self.check, 'kilo/y')), 1)
        self.assertEqual(len(bench_kilo.config_problems(None, self.check, 'kilo/x')), 1)

    def test_resolved_config_reads_kilo_debug_config(self):
        with tempfile.TemporaryDirectory() as d:
            fake = os.path.join(d, 'kilo.py')
            open(fake, 'w').write('import json, os, sys\nassert sys.argv[1:] == ["debug", "config"]\n'
                                  'print(json.dumps({"model": "kilo/x", "home": os.environ["XDG_CONFIG_HOME"]}))\n')
            env = dict(os.environ, XDG_CONFIG_HOME=d)
            got = bench_kilo.resolved_config([sys.executable, '-I', fake], env, d)
            self.assertEqual(got, {'model': 'kilo/x', 'home': d})

    def test_sandbox_env_hides_the_global_configuration(self):
        with tempfile.TemporaryDirectory() as d:
            ws = os.path.join(d, 'model', '82000000')
            os.makedirs(ws)
            with mock.patch.dict(os.environ, CD2_CHECK=self.check, KILO_CONFIG='x', KILO_CONFIG_DIR='y'):
                env = bench_kilo.sandbox_env(ws, 'kilo/x')
            self.assertEqual(env['XDG_CONFIG_HOME'], os.path.join(d, '.kilo-config-home'))
            self.assertTrue(os.path.isdir(env['XDG_CONFIG_HOME']))
            self.assertNotIn('KILO_CONFIG', env)
            self.assertNotIn('KILO_CONFIG_DIR', env)
            self.assertEqual(json.loads(env['KILO_CONFIG_CONTENT']),
                             dict(model='kilo/x', permission=bench_kilo.rules(self.check)))


if __name__ == '__main__':
    unittest.main()
