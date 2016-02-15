names = [line.strip().lower() for line in file('Problem22.txt').read().replace('"','').split(',')]
print sum((i+1) * sum(ord(c)-ord('a')+1 for c in names[i]) for i in xrange(len(names.sort() or names)))
