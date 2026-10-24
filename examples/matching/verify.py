"""Re-verify the matching examples against the original game code.

usage: py -I verify.py <path to extracted default.exe>

The target bytes are read from your own copy of the extracted title-update executable (nothing from the game is
stored in this repository). Extract it with jeff: `jeff xex extract default_patched.xex` writes default.exe next to the
XEX (SHA1 of the XEX: EC7B163617CD725F50B0CCA665AAF943F9BC6D8A).

The XDK location comes from the repository's configuration (XDK_DIR, or local.json: see tools/cd2.py config --xdk).
Fields filled in by the linker (call targets, addresses of globals and strings) are masked; everything else must be
byte-identical.
"""
import os, struct, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', '..', 'tools'))
import coff  # noqa: E402
from verify_src import XDK, BIN, check_toolchain  # noqa: E402

check_toolchain()
FLAGS = ['/nologo', '/c', '/Ox', '/Ob1', '/Gy', '/GF', '/GR-', '/GS-', '/fp:fast', '/D_XBOX', '/DNDEBUG']

# (source file, CD2 address, size in bytes, substring of the compiled symbol name)
EXAMPLES = [
    ('AI_cTrainingMission_StartMission.cpp', 0x82480DA0, 88, 'StartMission@cTrainingMission'),
    ('UI_HUD_RaceHUD_OnEnter.cpp', 0x821E6878, 80, 'OnEnter@RaceHUD'),
    ('CHARACTER_cActionManager_DeactivateMainIF.cpp', 0x82302E10, 152, 'DeactivateMainIF'),
    ('Equip_cCloakingDevice_ClassGetter.cpp', 0x822F33C8, 156, 'GetCloakingDevice'),
    ('ClosestOfTwo.cpp', 0x82401C88, 128, '?Closest@@'),
    ('ClosestOfTwo_alt.cpp', 0x82401C88, 128, '?PickClosest@@'),
    ('Classify.cpp', 0x821D0CE0, 124, 'Classify@Owner'),
    ('Classify_alt.cpp', 0x821D0CE0, 124, 'Check@cBase'),
]


def read_va(exe, va, size):
    d = exe
    pe = struct.unpack('<I', d[0x3C:0x40])[0]
    nsec = struct.unpack('<H', d[pe + 6:pe + 8])[0]
    optsz = struct.unpack('<H', d[pe + 20:pe + 22])[0]
    base = struct.unpack('<I', d[pe + 24 + 28:pe + 24 + 32])[0]
    for i in range(nsec):
        o = pe + 24 + optsz + i * 40
        vs, sva, rs, ra = struct.unpack('<IIII', d[o + 8:o + 24])
        if base + sva <= va < base + sva + rs:
            off = ra + va - base - sva
            return d[off:off + size]
    raise ValueError('address %08X not in any section' % va)


def main():
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(2)
    exe = open(sys.argv[1], 'rb').read()
    env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'], INCLUDE=os.path.join(XDK, 'include', 'xbox'))
    tmp = tempfile.mkdtemp(prefix='cd2verify_')
    failures = 0
    for src, va, size, sym in EXAMPLES:
        obj = os.path.join(tmp, os.path.splitext(src)[0] + '.obj')
        r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/Fo' + obj, os.path.join(HERE, src)],
                           env=env, capture_output=True, text=True)
        if r.returncode:
            print('%-48s COMPILE ERROR\n%s' % (src, r.stdout + r.stderr))
            failures += 1
            continue
        target = read_va(exe, va, size)
        found = [(n, c, rel) for n, c, rel in coff.functions(obj) if sym in n]
        if not found:
            print('%-48s symbol %r not found' % (src, sym))
            failures += 1
            continue
        name, code, rel = found[0]
        exact, ratio = coff.compare(code, target, rel)
        failures += not exact
        print('%-48s %08X  %4d bytes  %s' % (src, va, size, 'EXACT' if exact else 'MISMATCH (%.1f%%)' % (100 * ratio)))
    print('\n%d of %d examples match' % (len(EXAMPLES) - failures, len(EXAMPLES)))
    sys.exit(1 if failures else 0)


if __name__ == '__main__':
    main()

