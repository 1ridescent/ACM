N = input()
S = list(raw_input())
x = 0
for i in range(N):
    x += S[i] == 'x'
if x <= N / 2:
    print N / 2 - x
    for i in range(N):
        if S[i] == 'X' and x < N / 2:
            S[i] = 'x'
            x += 1
elif x >= N / 2:
    print x - N / 2
    for i in range(N):
        if S[i] == 'x' and x > N / 2:
            S[i] = 'X'
            x -= 1
print "".join(S)
