prob4 = dict((comb, 0) for comb in xrange(9, 37))
prob6 = dict((comb, 0) for comb in xrange(6, 37))

for a in xrange(1, 5):
	for b in xrange(1, 5):
		for c in xrange(1, 5):
			for d in xrange(1, 5):
				for e in xrange(1, 5):
					for f in xrange(1, 5):
						for g in xrange(1, 5):
							for h in xrange(1, 5):
								for i in xrange(1, 5):
									prob4[a+b+c+d+e+f+g+h+i] += 1

for a in xrange(1, 7):
	for b in xrange(1, 7):
		for c in xrange(1, 7):
			for d in xrange(1, 7):
				for e in xrange(1, 7):
					for f in xrange(1, 7):
						prob6[a+b+c+d+e+f] += 1

wins = 0
losses = 0
draws = 0

for comb, prob in prob4.items():
	for comb6, cprob6 in prob6.items():
		cprob6 *= prob
		if comb6 == comb:
			draws += cprob6
		elif comb6 < comb:
			wins += cprob6
		else:
			losses += cprob6

print 'Win:', float(wins)    / float(wins + losses + draws)
print 'Lose:', float(losses) / float(wins + losses + draws)
print 'Draw:', float(draws)  / float(wins + losses + draws)
