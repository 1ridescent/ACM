N = int(raw_input())
A = raw_input().split();
for i in xrange(0, N):
	A[i] = int(A[i]) - 1
cycle = [0 for i in xrange(0, N)]
for i in xrange(0, N):
	x = i
	for j in xrange(1, N + 3):
		x = A[x]
		if(x == i):
			cycle[i] = j
			break

lcm = 1
low = 1
from fractions import gcd
for i in xrange(0, N):
	if(cycle[i] != 0):
		lcm = lcm * cycle[i] / gcd(lcm, cycle[i])
	else:
		x = i
		for j in xrange(1, N + 3):
			x = A[x]
			if(cycle[x] != 0):
				low = max(low, j)
				break

print ((low + lcm - 1) / lcm) * lcm
