#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

ll power(ll b, int e)
{
	if(e == 0) return 1;
	ll res = power(b, e / 2);
	res = (res * res) % mod;
	if(e % 2) res = (res * b) % mod;
	return res;
}
ll inv(ll x)
{
	return power(x, mod - 2);
}

const ll MAX = 300000;

ll fact[MAX + 10];
ll invfact[MAX + 10];
void precompute()
{
	fact[0] = 1;
	for(int i = 1; i <= MAX; i++)
		fact[i] = (fact[i - 1] * i) % mod;
	for(int i = 0; i <= MAX; i++)
		invfact[i] = inv(fact[i]);

}
ll choose(int n, int r)
{
	if(n < r) return 0;
	return ((fact[n] * invfact[n - r]) % mod * invfact[r]) % mod;
}
ll pick(int n, int r)
{
	if(n < r) return 0;
	return (fact[n] * inv(fact[n - r])) % mod;
}

int N, K;
ll A[MAX];

ll suff[20][MAX]; // [i][s]: sum from s to N of a_s * (s - 2 - 2^i) pick 2^i

int main()
{
	precompute();
	cin >> K;
	N = (1 << K);
	for(int i = N; i >= 1; i--) cin >> A[i];

	for(int i = 0; i < K; i++)
	{
		for(int s = 1; s <= N; s++)
		{
			suff[i][s] = ((A[s] * choose(s - 1 - (1 << i), (1 << i) - 1)) % mod * fact[1 << i]) % mod;
// 			suff[i][s] = (A[s] * pick(s - 2 - (1 << i), 1 << i)) % mod;
// 			printf("i=%d s=%d val=%d\n", i, s, (int)suff[i][s]);
		}
		for(int s = N - 1; s >= 1; s--)
			suff[i][s] = (suff[i][s] + suff[i][s + 1]) % mod;
	}
	ll ans = 0;
	for(int s = 1; s <= N; s++)
		for(int i = 0; i < K; i++)
		{
			ll add = fact[N - 2 * (1 << i)];
			add = (add * choose(s - 1, (1 << i) - 1)) % mod;
			add = (add * fact[1 << i]) % mod;
			add = (add * A[s]) % mod;
			add = (add * suff[i][s + 1]) % mod;
			add = (add * N / 2 / (1 << i)) % mod;
			ans = (ans + 2 * add) % mod;
		}
	cout << (ans * invfact[N]) % mod;
}
