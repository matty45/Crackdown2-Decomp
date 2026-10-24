import struct, sys
# write a PPCBE COFF object with one zero-filled read-only data section (stand-in for .pdata in relink tests)
out, secname, size = sys.argv[1], sys.argv[2].encode(), int(sys.argv[3], 16)
hdr_size = 20 + 40
data_off = hdr_size
sym_off = data_off + size
fh = struct.pack('<HHIIIHH', 0x1F2, 1, 0, sym_off, 1, 0, 0)
sh = struct.pack('<8sIIIIIIHHI', secname[:8].ljust(8, b'\0'), 0, 0, size, data_off, 0, 0, 0, 0, 0x40300040)
sym = struct.pack('<8sIhHBB', b'pdpad\0\0\0', 0, 1, 0, 2, 0)
open(out, 'wb').write(fh + sh + b'\0' * size + sym + struct.pack('<I', 4))
