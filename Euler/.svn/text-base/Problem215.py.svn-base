import psyco
psyco.full()

def W(width, height):
	maxlen = (width + 1) / 2
	
	def inc(list, start):
		carry = True
		for i in xrange(start, len(list)):
			if carry:
				if list[i] == 0:
					list[i] = 1
					carry = False
					break
				else:
					list[i] = 0
		
		if carry:
			list.append(0)
	
	def tlen(list):
		ret = 0
		
		for elem in list:
			ret += (elem == 0) and 2 or 3
		
		return ret
	
	def isCracked(a, b):
		alen = len(a)
		blen = len(b)
		
		asize = bsize = 0
		apos = bpos = 0
		
		while (asize < width or bsize < width) and (apos < alen or bpos < blen):
			if apos < alen and (asize == 0 or asize < bsize):
				asize += (a[apos] == 0) and 2 or 3
				apos += 1
			elif bpos < blen and (bsize == 0 or bsize < asize):
				bsize += (b[bpos] == 0) and 2 or 3
				bpos += 1
			if asize != width and bsize != width and bsize == asize:
				return True
		
		return False
	
	comb = 0
	a = [0]
	b = [1] * maxlen # A hack to make it hit if len(b) >= maxlen
	
	while True:
		if len(b) >= maxlen:
			b = [1]
			inc(a, 1)
			while tlen(a) != width and len(a) < maxlen:
				inc(a, 1)
			if len(a) >= maxlen:
				break
			continue
		if tlen(b) == width and not isCracked(a, b):
			print len(a), a, b
			comb += 1
		inc(b, 1)
		while tlen(b) != width and len(b) < maxlen:
			inc(b, 1)
	
	return (height - 1) ** comb

print W(9, 3)
#print W(32, 10)
