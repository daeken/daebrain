teen = (
	'',
	'one',
	'two',
	'three',
	'four',
	'five',
	'six',
	'seven',
	'eight',
	'nine',
	'ten',
	'eleven',
	'twelve',
	'thirteen',
	'fourteen',
	'fifteen',
	'sixteen',
	'seventeen',
	'eighteen',
	'nineteen',
)

tens = (
	'',
	'one',
	'twenty',
	'thirty',
	'forty',
	'fifty',
	'sixty',
	'seventy',
	'eighty',
	'ninety'
)

total = 0
for i in xrange(1, 1000):
	line = ''
	ti = i % 100
	if i >= 100:
		line += teen[i / 100]
		line += 'hundred'
	if i >= 100 and i % 100 > 0:
		line += 'and'
	if ti > 0:
		if ti < 20:
			line += teen[ti]
		else:
			line += tens[i / 10 % 10] + teen[i % 10]
	print line, len(line)
	total += len(line)
	
total += len('onethousand')

print total
