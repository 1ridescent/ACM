N = input()
A = map(int, raw_input().split())

X = [0] * (N + 1)
for i in range(1, N + 1):
    X[i] = X[i - 1] ^ i
    #print X[i]

Q = 0
for i in range(1, N + 1):
    Q ^= A[i - 1]
    q = int(N / i)
    r = N % i
    if(q % 2 == 1):
        Q ^= X[i - 1]
    Q ^= X[r]
    #print Q

print Q
