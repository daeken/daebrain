count = 0

for p1 in xrange(201):
	print p1
	for p2 in xrange(101):
		tp2 = p2*2
		total = p1+tp2
		if total > 200:
			break
		for p5 in xrange(41):
			tp5 = p5*5
			total = p1+tp2+tp5
			if total > 200:
				break
			for p10 in xrange(21):
				tp10 = p10*10
				total = p1+tp2+tp5+tp10
				if total > 200:
					break
				for p20 in xrange(11):
					tp20 = p20*20
					total = p1+tp2+tp5+tp10+tp20
					if total > 200:
						break
					for p50 in xrange(5):
						tp50 = p50*50
						total = p1+tp2+tp5+tp10+tp20+tp50
						if total > 200:
							break
						for po1 in xrange(3):
							tpo1 = po1*100
							total = p1+tp2+tp5+tp10+tp20+tp50+tpo1
							if total > 200:
								break
							for po2 in xrange(2):
								total = p1+tp2+tp5+tp10+tp20+tp50+tpo1+(po2*200)
								if total == 200:
									count += 1

print count
