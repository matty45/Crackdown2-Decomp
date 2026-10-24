import sys, os
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import coff
P = os.path.dirname(os.path.abspath(__file__))
res = {m: {n: c.hex() for n, c, r in coff.functions(os.path.join(P, 'fp_%s.obj' % m))} for m in ('precise', 'fast', 'strict')}
for n in res['precise']:
    print('%-22s precise==fast:%s precise==strict:%s  precise=%s fast=%s' % (n[:22], res['precise'][n] == res['fast'].get(n), res['precise'][n] == res['strict'].get(n), res['precise'][n][:40], res['fast'].get(n, '')[:40]))
