"""Write config/library_splits.txt from libmap.json: one entry per library object, its block(s) in CD2's .text and the
evidence count. usage: py -I writelib.py <work dir>"""
import sys, json, os, re, collections
sys.path.insert(0, 'tools')
import cd2

W = sys.argv[1]
L = json.load(open(os.path.join(W, 'libmap.json')))
assign = {int(a, 16): v for a, v in L['assign'].items()}
multi = set(L['multi'])
mods = json.load(open(os.path.join(W, 'anchors.json')))['mods']
syms = cd2.jeff_symbols()
body = [a for a in sorted(syms) if a in assign]
blocks = []
order = sorted(syms)
pos = {a: i for i, a in enumerate(order)}
for a in body:
    m = assign[a]['mod']
    if blocks and blocks[-1][0] == m and pos[a] == pos[blocks[-1][2]] + 1:
        blocks[-1][2] = a
        blocks[-1][3][assign[a]['how']] += 1
    else:
        blocks.append([m, a, a, collections.Counter({assign[a]['how']: 1})])
per = collections.defaultdict(list)
for b in blocks:
    per[b[0]].append(b)


def label(m):
    md = mods[str(m)]
    lib = re.split(r'[\\/]', md['obj'])[-1]
    obj = re.split(r'[\\/]', md['name'])[-1]
    return '%s(%s)' % (lib, obj) if lib.lower().endswith('.lib') else obj


lines = ['# config/library_splits.txt: which addresses of Crackdown 2 belong to which library (or other non-source) object.',
         '# Maintainer-owned, like config/splits.txt, but for code that is linked from libraries rather than decompiled:',
         '# the XDK (d3d9, d3dx9, xgraphics, xaudio2, xapi, CRT, ...), Havok, Wwise, Scaleform, XLSP and so on.',
         '#',
         '# <library>(<object>)      the object, as RuffKing\'s PDB names it',
         '#   text <start> <end>      a block [start, end) of its functions',
         '#   hot <addr>              one of its functions that the link order list moved into 0x821D0000-0x823D0000',
         '#   init <addr>             one of its functions in the initializer region (from 0x82F00000)',
         '#',
         '# Evidence (method: tools/research/splits_libs/README.md). A CD2 function is identified with a RuffKing function',
         '# of at least 64 bytes when their code, with address immediates masked, is identical and unique in both builds',
         '# (or all copies lie in one RuffKing object), or when the RuffKing name table (data/symbols) names it. Its',
         '# object is the RuffKing PDB section contribution holding that function. Unidentified functions between two',
         '# identified functions of one object belong to it (the linker lays out each object contiguously); at a',
         '# boundary between two objects, functions are assigned while their sizes repeat the RuffKing functions after',
         '# the first object\'s last match or before the second\'s first. Short runs of an object that has a longer run',
         '# elsewhere are template/inline copies kept from another object and are not used as evidence. Game files',
         '# (config/splits.txt) take precedence: nothing inside them is assigned here.',
         '# Counts per block: identified / contiguity / boundary-size. Objects with more than one block are marked',
         '# "several blocks: review": both cannot be right unless the linker split the object.',
         '']
hot = collections.defaultdict(list)
for a, m in L.get('hot', {}).items():
    hot[m].append(int(a, 16))
for a, m in L.get('init', {}).items():
    hot[m].append(int(a, 16))  # initializer-region functions are listed like order-list ones, by address
for m in hot:
    per.setdefault(m, [])
n_fun = 0
key = lambda x: x[1][0][1] if x[1] else min(hot[x[0]]) + 0x100000000
for m, bs in sorted(per.items(), key=key):
    lines.append(label(m))
    for a in sorted(hot.get(m, [])):
        if a >= 0x82F00000:
            lines.append('  init 0x%08X   # initializer region: its code references only this object\'s functions' % a)
        else:
            lines.append('  hot 0x%08X   # identified (code, >= 64 bytes)' % a)
        n_fun += 1
    for b in bs:
        end = b[2] + syms[b[2]][1]
        n = sum(b[3].values())
        n_fun += n
        lines.append('  text 0x%08X 0x%08X   # %d functions: %d / %d / %d%s' % (
            b[1], end, n, b[3]['identified'], b[3]['contiguity'], b[3]['boundary-size'],
            '; several blocks: review' if len(bs) > 1 else ''))
    lines.append('')
open('config/library_splits.txt', 'w', newline='\n').write('\n'.join(lines))
print('%d objects, %d blocks, %d functions written' % (len(per), len(blocks), n_fun))
