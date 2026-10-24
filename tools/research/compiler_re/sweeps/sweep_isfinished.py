"""Sweep source shapes for the inline cAmbientVFXSpawnerBase::IsVFXFinished body; compare cAmbientVFXSpawner::IsVFXFinished."""
import os, subprocess, sys
ROOT = r'<repo>'
sys.path.insert(0, os.path.join(ROOT, 'tools'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'research', 'scripts'))
import coff
from verify_src import FLAGS, XDK, BIN, pe_reader

exe, WORK = sys.argv[1], sys.argv[2]
read, _ = pe_reader(open(exe, 'rb').read())
target = read(0x827F9748, 164)
HDR = os.path.join(ROOT, 'include', 'VFX', 'cAmbientVFXSpawner.h')
OLD = ('            unsigned int flags = m_pVFXInstance->m_Flags;\n'
       '            unsigned char bFinished = m_pVFXInstance->m_bFinishedBit != 0 || (flags & 0x400B) == 0;\n'
       '            return bFinished != 0;\n')
P = '            unsigned int flags = m_pVFXInstance->m_Flags;\n'
V = {
    'orig': OLD,
    'bit_uint_local': P + '            unsigned int bit = (flags >> 12) & 1;\n            unsigned char b = bit != 0 || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'bit_uchar_local': P + '            unsigned char bit = (unsigned char)((flags >> 12) & 1);\n            unsigned char b = bit != 0 || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'bit_bool_local': P + '            bool bit = ((flags >> 12) & 1) != 0;\n            unsigned char b = bit || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'bitfield_local': '            unsigned int bit = m_pVFXInstance->m_bFinishedBit;\n' + P + '            unsigned char b = bit != 0 || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'bitfield_uchar': '            unsigned char bit = (unsigned char)m_pVFXInstance->m_bFinishedBit;\n' + P + '            unsigned char b = bit || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'bit_eq1': P + '            unsigned char b = ((flags >> 12) & 1) == 1 || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'bitfield_eq1': P + '            unsigned char b = m_pVFXInstance->m_bFinishedBit == 1 || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'mask_shift': P + '            unsigned char b = ((flags & 0x1000) >> 12) != 0 || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'bit_int_local': P + '            int bit = (int)((flags >> 12) & 1);\n            unsigned char b = bit != 0 || (flags & 0x400B) == 0;\n            return b != 0;\n',
    'ternary': P + '            unsigned char b = ((flags >> 12) & 1) ? 1 : ((flags & 0x400B) == 0);\n            return b != 0;\n',
}
env = dict(os.environ, PATH=BIN + ';' + os.environ['PATH'],
           INCLUDE=os.path.join(XDK, 'include', 'xbox') + ';' + os.path.join(ROOT, 'include'))
text = open(HDR).read()
assert OLD in text, 'body not found'
for k, v in V.items():
    d = os.path.join(WORK, k)
    os.makedirs(os.path.join(d, 'VFX'), exist_ok=True)
    open(os.path.join(d, 'VFX', 'cAmbientVFXSpawner.h'), 'w').write(text.replace(OLD, v))
    obj = os.path.join(d, 'o.obj')
    r = subprocess.run([os.path.join(BIN, 'cl.exe')] + FLAGS + ['/I' + d, '/Fo' + obj,
                       os.path.join(ROOT, 'src', 'VFX', 'cAmbientVFXSpawner.cpp')], env=env, capture_output=True, text=True)
    if r.returncode:
        print('%-16s compile error: %s' % (k, (r.stdout + r.stderr).strip().splitlines()[-1][:100]))
        continue
    name, code, rel = [x for x in coff.functions(obj) if '?IsVFXFinished@cAmbientVFXSpawner@' in x[0]][0]
    exact, ratio = coff.compare(code, target, rel)
    print('%-16s %s %5.1f%%  extrwi:%s' % (k, 'EXACT' if exact else '     ', 100 * ratio, 'yes' if b'\x55\x6a\xa7\xfe' in code else 'no'))
