def rotate(n):
	s = str(n)
	return int(s[-1] + s[:-1])

for i in xrange(10, 100000):
	if int(str(i % 10) * len(str(i))) == i:
		continue
	roti = rotate(i)
	if roti % i == 0:
		print i, roti

print sum(i for i in xrange(10, 1000000) for roti in (rotate(i), ) if i != roti and roti % i == 0)
