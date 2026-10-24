"""Try source shapes for CalcRandInitSpawnTime's expression; report whether the target's fmuls word ECE802F2 appears."""
import os, re, struct, subprocess, sys
ROOT = r'<repo>'
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'research', 'scripts'))
import coff
from verify_src import FLAGS, XDK, BIN

SRC = os.path.join(ROOT, 'src', 'VFX', 'cAmbientVFXSpawner.cpp')
WORK = sys.argv[1]
OLD = ('float f = (float)ms_RandGen.Rand() * (proto->m_fInitSpawnTimeMax - proto->m_fInitSpawnTimeMin) * 0.000030518509f\n'
       '            + proto->m_fInitSpawnTimeMin;')
MIN, MAX, R = 'proto->m_fInitSpawnTimeMin', 'proto->m_fInitSpawnTimeMax', 'ms_RandGen.Rand()'
V = {
    'orig':        'float f = (float)%(R)s * (%(MAX)s - %(MIN)s) * 0.000030518509f + %(MIN)s;',
    'div':         'float f = (float)%(R)s / 32767.0f * (%(MAX)s - %(MIN)s) + %(MIN)s;',
    'div_paren':   'float f = ((float)%(R)s / 32767.0f) * (%(MAX)s - %(MIN)s) + %(MIN)s;',
    'div_rev':     'float f = (%(MAX)s - %(MIN)s) * ((float)%(R)s / 32767.0f) + %(MIN)s;',
    'div_minfirst':'float f = %(MIN)s + ((float)%(R)s / 32767.0f) * (%(MAX)s - %(MIN)s);',
    'div_minfirst_rev': 'float f = %(MIN)s + (%(MAX)s - %(MIN)s) * ((float)%(R)s / 32767.0f);',
    'k_mid':       'float f = (float)%(R)s * 0.000030518509f * (%(MAX)s - %(MIN)s) + %(MIN)s;',
    'k_first':     'float f = 0.000030518509f * (float)%(R)s * (%(MAX)s - %(MIN)s) + %(MIN)s;',
    'range_local': 'float range = %(MAX)s - %(MIN)s; float f = (float)%(R)s * range * 0.000030518509f + %(MIN)s;',
    'rand_local':  'float r = (float)%(R)s; float f = r * (%(MAX)s - %(MIN)s) * 0.000030518509f + %(MIN)s;',
    'rand_local_div': 'float r = (float)%(R)s / 32767.0f; float f = r * (%(MAX)s - %(MIN)s) + %(MIN)s;',
    'unit_local':  'float t = (float)%(R)s * 0.000030518509f; float f = %(MIN)s + (%(MAX)s - %(MIN)s) * t;',
    'unit_local2': 'float t = (float)%(R)s * 0.000030518509f; float f = t * (%(MAX)s - %(MIN)s) + %(MIN)s;',
    'lerp':        'float t = (float)%(R)s / 32767.0f; float f = %(MIN)s * (1.0f - t) + %(MAX)s * t;',
    'minfirst':    'float f = %(MIN)s + (float)%(R)s * (%(MAX)s - %(MIN)s) * 0.000030518509f;',
    'minfirst_k_first': 'float f = %(MIN)s + 0.000030518509f * (float)%(R)s * (%(MAX)s - %(MIN)s);',
}
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
           INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
text = open(SRC).read()
assert OLD in text, 'expression not found'
os.makedirs(WORK, exist_ok=True)
for k, v in V.items():
    p = os.path.join(WORK, 'v_%s.cpp' % k)
    open(p, 'w').write(text.replace(OLD, v % dict(R=R, MIN=MIN, MAX=MAX)))
    obj = p[:-4] + '.obj'
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + os.path.dirname(SRC), '/Fo' + obj, p],
                       env=env, capture_output=True, text=True)
    if r.returncode:
        print('%-18s compile error' % k)
        continue
    code = [c for n, c, rel in coff.functions(obj) if 'CalcRandInitSpawnTime' in n][0]
    ws = struct.unpack('>%dI' % (len(code) // 4), code)
    fm = ['%08X' % w for w in ws if w >> 26 == 59]  # single-precision arithmetic (fmuls/fmadds/fsubs...)
    print('%-18s %2d words  target fmuls %-3s  fp ops: %s' % (k, len(ws), 'YES' if 0xECE802F2 in ws else 'no', ' '.join(fm)))
