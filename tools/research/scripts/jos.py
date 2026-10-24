import re, json, sys
S = sys.argv[1]
asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
jeff = {int(m.group(1), 16): int(m.group(2), 16) for m in re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn ', asm)}
only = json.load(open(S + r'\jeff_only.json'))['all']
json.dump([[ea, jeff[ea]] for ea in only], open(S + r'\jeff_only_sized.json', 'w'))
print(len(only))
