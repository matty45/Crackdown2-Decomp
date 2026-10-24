import struct, sys

KEYS = {0x000002FF: 'resource_info', 0x000003FF: 'base_file_format', 0x00010001: 'image_base?',
        0x000103FF: 'import_libraries', 0x000183FF: 'original_pe_name', 0x000200FF: 'static_libraries',
        0x00040006: 'execution_info', 0x00010100: 'entry_point', 0x00010201: 'image_base',
        0x00020104: 'tls_info', 0x00020200: 'default_stack_size', 0x00030000: 'system_flags'}

def main(path):
    d = open(path, 'rb').read()
    magic, mflags, pe_off, _, sec_off, nopt = struct.unpack('>4sIIIII', d[:24])
    print(path, magic, 'module_flags=%x pe_off=%x sec_off=%x nopt=%d size=%d' % (mflags, pe_off, sec_off, nopt, len(d)))
    for i in range(nopt):
        key, val = struct.unpack('>II', d[24 + i * 8:32 + i * 8])
        name = KEYS.get(key, '?')
        print('  opt %08x %-18s val=%08x' % (key, name, val))
        if key == 0x000200FF:
            size = struct.unpack('>I', d[val:val + 4])[0]
            for off in range(val + 4, val + size, 16):
                nm = d[off:off + 8].rstrip(b'\0').decode()
                maj, mi, bld, qfe = struct.unpack('>HHHH', d[off + 8:off + 16])
                print('     lib %-10s %d.%d.%d.%d approval=%d' % (nm, maj, mi, bld, qfe & 0xFF, qfe >> 13))
        elif key == 0x000003FF:
            size, enc, comp = struct.unpack('>IHH', d[val:val + 8])
            print('     encryption=%d compression=%d' % (enc, comp))
        elif key == 0x000183FF:
            size = struct.unpack('>I', d[val:val + 4])[0]
            print('     ', d[val + 4:val + size].rstrip(b'\0'))
    pe = d[pe_off:pe_off + 0x400]
    print('  basefile starts with', pe[:2], ' Rich' if b'Rich' in pe else ' (no plain Rich marker in first 0x400)')

for p in sys.argv[1:]:
    main(p)
