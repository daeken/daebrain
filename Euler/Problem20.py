print sum(int(c) for c in str(reduce(lambda a,b:a*b, xrange(2,101))))
