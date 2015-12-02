#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
long long modex(int a, int p) {
	if (!p) return 1;
	if (p & 1) return (modex(a, p - 1) * a) % MOD;
	long long m = modex(a, p >> 1);
	return (m * m) % MOD;
}
int main() {
	int N;
	scanf("%d", &N);
	long long sum = 1, sumsq = 1, e = 1, esq = 1;
	long long inv2 = modex(2, MOD - 2);
	for (int i = 1; i <= N; ++i) {
		long long iinv = modex(i, MOD - 2);
		e = (2 * sum * iinv) % MOD;
		esq = (2 * iinv * sumsq) % MOD;
		esq = (esq + ((((2 * iinv * iinv) % MOD) * sum) % MOD) * sum) % MOD;
		sum = (sum + e) % MOD;
		sumsq = (sumsq + esq) % MOD;
	}
	long long ans = (esq - e * e) % MOD;
	if (ans < 0) ans += MOD;
	printf("%lld\n", ans);
}