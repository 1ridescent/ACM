#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
long long modex(int a, int p) {
	if (!p) return 1;
	if (p & 1) return (modex(a, p - 1) * a) % MOD;
	long long m = modex(a, p >> 1);
	return (m * m) % MOD;
}
int A[50];
int N = 8;
double sumprob;
void go(int n, double p) {
	if (n == N) {
		sumprob += p * A[n];
		return;
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			A[n + 1] = A[i] + A[j];
			go(n + 1, p / (n + 1) / (n + 1));
		}
	}
}
int main() {
	A[0] = 1;
	go(0, 1);
	printf("%.9lf\n", sumprob);
}