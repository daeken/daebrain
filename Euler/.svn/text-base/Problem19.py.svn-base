day = 1
count = 0
for year in xrange(1900, 2001):
	for month in xrange(12):
		if year >= 1901 and day == 0:
			count += 1
		if month in (0, 2, 4, 6, 7, 9, 11):
			day += 31
		elif month == 1:
			day += 28
			if year % 4 == 0 and (year % 100 != 0 or year % 400 == 0):
				day += 1
		else:
			day += 30
		day %= 7

print count
