"""One-time bootstrap of config/splits.txt from the agents' recorded split decisions (results.json per packet).

For each source file: the main-body range runs from the first belonging candidate to the first candidate after the
last belonging one (packet candidates are consecutive functions); functions in the order-list region
(0x821D0000-0x823D0000) and the initializer area are listed individually. Addresses in FOLDED (identical-code-folded
copies owned by another file, see docs) are excluded. Prints the splits text; review it before committing.
usage: py -I splits_bootstrap.py <scratchpad dir>
"""
import glob, json, os, sys

S = sys.argv[1]
HOT = (0x821D0000, 0x823D0000)
INIT = 0x82F00000
PACKETS = [
    ('src/CHARACTER/cNPCTintProfile.cpp', S + r'\tupilot', S + r'\tupilot\results.json'),
    ('src/GangManager/cFactionConfigData.cpp', S + r'\tupilot2', S + r'\tupilot2\results.json'),
    ('src/VFX/cAmbientVFXSpawner.cpp', S + r'\batch\cAmbientVFXSpawner\cAmbientVFXSpawner', None),
    ('src/VFX/cRopes.cpp', S + r'\batch\cRopes\cRopes', None),
    ('src/GameManagement/cGameModeArena.cpp', S + r'\batch\cGameModeArena\cGameModeArena', None),
    ('src/AI/cChaseBehaviour.cpp', S + r'\batch2\cChaseBehaviour_r2\cChaseBehaviour', None),
    ('src/Equip/DLCWeapons/cFlocket.cpp', S + r'\batch2\cFlocket\cFlocket', None),
    ('src/VEHICLE_CONTROL/cHelicopterController.cpp', S + r'\batch2\cHelicopterController\cHelicopterController', None),
]
FOLDED = {0x824D2850: 'MakeNew shared by cAgressiveResponseBase, cChaseBehaviour, cAgressiveResponsePilotBehaviour, '
                      'cChaseAndAttackPilotBehaviour (registrar data); the surviving copy lies between BreachPilot and '
                      'cChaseAndAttackPilotBehaviour code'}


def ids(fid):
    """'F07' -> [7]; 'F01-F25' -> [1..25]"""
    a, _, b = fid.partition('-')
    lo = int(a.lstrip('F'))
    return list(range(lo, int(b.lstrip('F')) + 1)) if b else [lo]


def norm(fid):
    return ids(fid)[0]


REGS = json.load(open(os.path.join(S, 'cd2_registrars.json')))
INITS = {r['init'] for r in REGS if r.get('init')}
ATEXITS = {r['atexit'] for r in REGS if r.get('atexit')}


out = []
for src, pdir, rjson in PACKETS:
    tdirs = glob.glob(os.path.join(pdir, '**', 'targets', 'F*_*'), recursive=True)
    cands = {}
    for d in tdirs:
        k, a = os.path.basename(d).split('_')
        size = len(open(os.path.join(d, 'target.hex')).read().strip()) // 2
        cands[norm(k)] = (int(a, 16), size)
    rpath = rjson or os.path.join(pdir, 'results.json')
    res = {}
    for f in json.load(open(rpath))['functions']:
        for k in ids(f['id']):
            res[k] = f
    belong = {k for k, f in res.items() if f.get('belongs') is True}
    body = sorted((a, s, k) for k, (a, s) in cands.items() if not HOT[0] <= a < HOT[1] and a < INIT and a not in FOLDED)
    bel = [(a, s, k) for a, s, k in body if k in belong]
    start = bel[0][0]
    last = bel[-1]
    after = [a for a, s, k in body if a > last[0]]
    end, open_end = (after[0], False) if after else (last[0] + last[1], True)
    inside_foreign = [k for a, s, k in body if start <= a < end and k not in belong]
    out.append('%s' % src)
    out.append('  text 0x%08X 0x%08X%s' % (start, end, '   # end = end of last known function (window ended)' if open_end else ''))
    if inside_foreign:
        out.append('  # WARNING: candidates inside the range judged not to belong: %s' % ', '.join('F%02d' % k for k in inside_foreign))
    for a, s in sorted(cands.values()):
        k = [kk for kk, v in cands.items() if v[0] == a][0]
        if k not in belong:
            continue
        if HOT[0] <= a < HOT[1]:
            out.append('  hot 0x%08X' % a)
        elif a >= INIT:
            out.append('  %s 0x%08X' % ('init' if a in INITS else 'atexit' if a in ATEXITS else 'initarea?', a))
        elif a in FOLDED:
            out.append('  folded 0x%08X  # %s' % (a, FOLDED[a]))
    out.append('')
print('\n'.join(out))
