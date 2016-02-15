import math, psyco
psyco.full()

print sum(max(((a-1)**n + (a+1)**n) % asq for asq in (a**2, ) for n in xrange(2, a+1)) for a in xrange(3, 1001))
