import sys,re
fn=sys.argv[1]; sym=sys.argv[2]; tgt=sys.argv[3]
txt=open('t.dis').read().split('\n')
start=None; words=[]
for i,l in enumerate(txt):
    if l.startswith(sym): start=i; continue
    if start is not None:
        if l and not l.startswith(' ') and not l.startswith('$'): break
        m=re.match(r'\s+([0-9A-F]{8}): ([0-9A-F]{8}) ',l)
        if m: words.append((int(m.group(1),16),m.group(2),l[l.find(m.group(2))+9:].strip()))
t=re.sub(r'\s','',open(tgt).read())
tw=[t[i:i+8].upper() for i in range(0,len(t),8)]
print(len(words),len(tw))
for (a,w,txt_),x in zip(words,tw):
    if w!=x: print('%04X ours %s tgt %s  %s'%(a,w,x,txt_[:50]))
