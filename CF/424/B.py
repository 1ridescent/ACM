import math

N, cnt = map(int, raw_input().split())
A = []
for i in range(N):
    x, y, s = map(int, raw_input().split())
    A.append((x * x + y * y, s))
A.sort()
done = 0
for i in range(N):
    cnt += A[i][1]
    if(cnt >= 1000000):
        print math.sqrt(A[i][0])
        done = 1
        break
if not done:
    print -1
