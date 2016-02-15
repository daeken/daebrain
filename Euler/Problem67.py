tri = tuple([int(i) for i in line.strip().split(' ')] for line in file('Problem67.txt', 'r').readlines())

for row in xrange(len(tri)-2, -1, -1):
	cur, next = tri[row], tri[row+1]
	for col in xrange(row+1):
		a, b = next[col], next[col+1]
		if a < b:
			cur[col] += b
		else:
			cur[col] += a

print tri[0][0]
