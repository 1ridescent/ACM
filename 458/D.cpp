#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long double ld;

ld inf = 1e99;

ld choose[305][305];
ld logfact[100005];

int main() {
	memset(choose, 0, sizeof(choose));
	choose[0][0] = 1;
	for(int i = 1; i <= 302; i++) {
		choose[i][0] = choose[i][i] = 1;
		for(int j = 1; j < i; j++)
			choose[i][j] = min(choose[i - 1][j - 1] + choose[i - 1][j], inf);
	}
	logfact[0] = 0;
	for(int i = 1; i <= 100002; i++) logfact[i] = logfact[i - 1] + log(i);

	int N, M, K;
	cin >> N >> M >> K;

	ld res = 0;
	for(int r = 0; r <= N; r++) {
		for(int c = 0; c <= N; c++) {
			int n = r * N + c * N - r * c;
			if(n > K) continue;
			// (M - n) choose (k - n) / M choose k
			res += exp((logfact[M - n] - logfact[M - K] - logfact[K - n]) - (logfact[M] - logfact[M - K] - logfact[K])) * choose[N][r] * choose[N][c];
			res = min(res, inf);
		}
	}

	printf("%.12f\n", (double)res);
}
