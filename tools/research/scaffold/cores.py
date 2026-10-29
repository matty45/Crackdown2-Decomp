r"""Source-file cores for registered game classes, from CD2's own structure (no RuffKing code needed):

- RetClassName(): 'lis r3,hi(name); addi r3,r3,lo(name); blr', returning the registrar's class-name string, ties a
  registrar to its primary vtable (the vtable that holds that RetClassName).
- A class's markers: RetClassName, MakeNew (unless shared with another registrar), and the functions of its primary
  vtable that no other registered class's primary vtable holds (its own overrides), near RetClassName.
- The core runs from the first marker to the end of the last. It is accepted only if no other class's marker and no
  game function named from another RuffKing object lies inside, it stays out of the hot and initializer regions,
  overlaps no existing file, and the accepted cores appear in the order of their initializers (link order).

usage: py -I tools/research/scaffold/cores.py <work dir>      (writes <work dir>/cores.json)
"""
import bisect, collections, json, os, struct, sys

sys.path.insert(0, 'tools')
import importlib.util
spec = importlib.util.spec_from_file_location('cd2', 'tools/cd2.py')
cd2 = importlib.util.module_from_spec(spec)
spec.loader.exec_module(cd2)
from check_integrity import load_splits

S = sys.argv[1]
HOT = (0x821D0000, 0x823D0000)
INIT_REGION = 0x82F00000
NEAR = 0x8000          # an override counts as a marker only this close to RetClassName
BS = chr(92)

syms = cd2.jeff_symbols()
starts = sorted(syms)
R = json.load(open(os.path.join(S, 'cd2_registrars.json')))
V = json.load(open(os.path.join(S, 'cd2_vtables.json')))
A = json.load(open(os.path.join(S, 'anchors.json')))
mods = {int(k): v for k, v in A['mods'].items()}
anchors = {int(k, 16): v for k, v in A['anchors'].items()}


def words(a, n):
    return struct.unpack('>%dI' % n, cd2.read(a, 4 * n))


def returned_address(a):
    """The address a 12-byte 'lis r3; addi r3,r3; blr' function returns, else None."""
    if syms.get(a, (None, 0))[1] != 12:
        return None
    w = words(a, 3)
    rx = (w[0] >> 21) & 31
    # lis rX, hi ; addi r3, rX, lo ; blr
    if (w[0] >> 26 != 15 or (w[0] >> 16) & 31 or w[1] >> 26 != 14 or (w[1] >> 21) & 31 != 3
            or (w[1] >> 16) & 31 != rx or w[2] != 0x4E800020):
        return None
    lo = w[1] & 0xFFFF
    lo = lo - 0x10000 if lo & 0x8000 else lo
    return ((w[0] & 0xFFFF) << 16) + lo & 0xFFFFFFFF


# RetClassName per class-name string
by_str = collections.defaultdict(list)
for a in starts:
    if a < INIT_REGION:
        r = returned_address(a)
        if r is not None:
            by_str[r].append(a)

in_vtables = collections.defaultdict(set)
for va, slots in V:
    for f in slots:
        in_vtables[f].add(va)

classes = {}
makenew_count = collections.Counter(r['makenew'] for r in R)
for r in R:
    rcn = by_str.get(r['str'], [])
    vts = [va for va, slots in V if any(f in rcn for f in slots)]
    classes[r['name']] = dict(reg=r, rcn=rcn, vts=vts)
primary_slots = {n: {f for va, slots in V if va in c['vts'] for f in slots} for n, c in classes.items()}
holders = collections.Counter(f for s in primary_slots.values() for f in s)

game = lambda m: (BS + 'Projects' + BS) in mods[m]['objname'] or (BS + 'Game' + BS) in mods[m]['objname']
markers = {}
for n, c in classes.items():
    if len(c['rcn']) != 1:
        continue
    rc = c['rcn'][0]
    if HOT[0] <= rc < HOT[1]:
        continue
    m = {rc}
    mk = c['reg']['makenew']
    if makenew_count[mk] == 1 and mk in syms and not HOT[0] <= mk < HOT[1]:
        m.add(mk)
    for f in primary_slots[n]:
        if holders[f] == 1 and f in syms and abs(f - rc) < NEAR and not HOT[0] <= f < HOT[1] and f < INIT_REGION:
            m.add(f)
    markers[n] = m
owner = {}
for n, ms in markers.items():
    for f in ms:
        owner.setdefault(f, set()).add(n)

existing = load_splits('config/splits.txt')
taken = [e['text'] for e in existing.values() if e.get('text')]
cores, rejected = [], collections.Counter()
game_anchors = sorted(a for a, v in anchors.items() if game(v['mod']))
for n, ms in markers.items():
    lo = min(ms)
    hi = max(ms) + syms[max(ms)][1]
    why = None
    if len(ms) < 2:
        why = 'one marker only'
    elif hi - lo > 0x20000:
        why = 'markers too far apart'
    elif any(lo <= f < hi and n not in o for f, o in owner.items()):
        why = 'another class\'s marker inside'
    elif any(lo < t[1] and t[0] < hi for t in taken):
        why = 'overlaps an existing file'
    elif lo < HOT[1] and hi > HOT[0]:
        why = 'touches the hot region'
    else:
        inside = {anchors[a]['mod'] for a in game_anchors if lo <= a < hi}
        if len(inside) > 1:
            why = 'functions of several RuffKing objects inside'
    if why:
        rejected[why] += 1
        continue
    r = classes[n]['reg']
    cores.append(dict(name=n, lo=lo, hi=hi, markers=sorted(ms), init=r['init'], atexit=r['atexit'],
                      makenew=r['makenew'], size=r['size'], funcs=sum(1 for a in starts if lo <= a < hi)))

# link order: initializers and text must agree; keep the longest increasing run (drop the rest)
cores.sort(key=lambda c: c['init'])
n = len(cores)
best, prev = [1] * n, [-1] * n
for i in range(n):
    for j in range(i):
        if cores[j]['lo'] < cores[i]['lo'] and best[j] + 1 > best[i]:
            best[i], prev[i] = best[j] + 1, j
i = max(range(n), key=lambda k: best[k]) if n else -1
keep = set()
while i >= 0:
    keep.add(i)
    i = prev[i]
dropped = n - len(keep)
cores = [c for k, c in enumerate(cores) if k in keep]
# no overlaps between accepted cores
cores.sort(key=lambda c: c['lo'])
ok = [c for k, c in enumerate(cores) if k == 0 or cores[k - 1]['hi'] <= c['lo']]
print('%d registrars; %d with one RetClassName; %d cores accepted (%d functions), %d dropped by link order, %d by overlap'
      % (len(R), sum(len(c['rcn']) == 1 for c in classes.values()), len(ok), sum(c['funcs'] for c in ok), dropped,
         len(cores) - len(ok)))
print('rejected:', dict(rejected))

print('\nvalidation against the verified files (the class core must lie inside the verified range):')
verified = {'cChaseBehaviour': 'src/AI/cChaseBehaviour.cpp', 'cNPCTintProfile': 'src/CHARACTER/cNPCTintProfile.cpp',
            'cFlocket': 'src/Equip/DLCWeapons/cFlocket.cpp', 'cFactionConfigData': 'src/GangManager/cFactionConfigData.cpp',
            'cHelicopterController': 'src/VEHICLE_CONTROL/cHelicopterController.cpp',
            'cAmbientVFXSpawner': 'src/VFX/cAmbientVFXSpawner.cpp', 'cRopes': 'src/VFX/cRopes.cpp',
            'cGameModeArena': 'src/GameManagement/cGameModeArena.cpp'}
for cname, f in verified.items():
    ms = markers.get(cname)
    vlo, vhi = existing[f]['text']
    if not ms:
        print('  %-22s no markers (RetClassName: %s)' % (cname, [hex(x) for x in classes.get(cname, {}).get('rcn', [])]))
        continue
    lo, hi = min(ms), max(ms) + syms[max(ms)][1]
    print('  %-22s markers %d  core %08X-%08X  verified %08X-%08X  %s' % (
        cname, len(ms), lo, hi, vlo, vhi, 'INSIDE' if vlo <= lo and hi <= vhi else 'OUTSIDE'))
json.dump(ok, open(os.path.join(S, 'cores.json'), 'w'), indent=1)
