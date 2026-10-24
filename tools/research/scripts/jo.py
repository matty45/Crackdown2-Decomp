import re, json, sys, random
S = sys.argv[1]
asm = open(S + r'\jeffwork2\out\asm\auto_02_821D0000_text.s').read()
jeff = {int(m.group(1), 16): int(m.group(2), 16) for m in re.finditer(r'# \.text:0x[0-9A-F]+ \| 0x([0-9A-F]{8}) \| size: 0x([0-9A-F]+)\n\.fn ', asm)}
ida = {json.loads(l)['ea'] for l in open(S + r'\cd2_funcs.jsonl')}
only = sorted(ea for ea in jeff if ea not in ida)
random.seed(3)
json.dump({'sample': random.sample(only, 40), 'all': only}, open(S + r'\jeff_only.json', 'w'))
print(len(only))
