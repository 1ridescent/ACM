#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000033;

ll power(ll b, int e)
{
	if(e == 0) return 1;
	ll res = power(b, e / 2);
	res = (res * res) % mod;
	if(e % 2 == 1) res = (res * b) % mod;
	return res;
}
ll inv(ll b)
{
	return power(b, mod - 2);
}

ll perm[1234][1234];
ll fact[1234567];
ll invfact[1234567];
void precompute()
{
	perm[1][0] = 1;
	for(int n = 2; n <= 1200; n++)
	{
		perm[n][0] = perm[n][n - 1] = 1;
		int s = n - 1, t = 2;
		for(int m = 1; m < n - 1; m++)
		{
			perm[n][m] = (perm[n - 1][m - 1] * s + perm[n - 1][m] * t) % mod;
			s--;
			t++;
		}
	}
	fact[0] = 1;
	for(int i = 1; i <= 1234000; i++) fact[i] = (fact[i - 1] * i) % mod;
	for(int i = 0; i <= 1234000; i++) invfact[i] = inv(fact[i]);
}

ll choose(int n, int k)
{
	return (fact[n] * ((invfact[n - k] * invfact[k]) % mod)) % mod;
}
ll urns(int n, int r)
{
	return choose(n + r - 1, r - 1);
}

ll all(ll N, ll M)
{
	ll total = 0;
	for(int k = 0; k < M; k++)
	{
		ll need = N * M;
		ll have = M * (M - 1) - k * M;
		ll n = (need - have) / M;
		if(n < 0) continue;
		total = (total + perm[M][k] * urns(n, M)) % mod;
	}
	return total;
}
ll compute(ll N, ll M)
{
	ll total[1005];
	for(int m = 1; m <= M; m++)
	{
		total[m] = all(N, m);
		for(int i = 1; i < m; i++)
			if(m % i == 0)
				total[m] = (total[m] - total[i] + mod) % mod;
	}
	return (total[M] * inv(M)) % mod;
}

int main()
{
	precompute();
	//for(int i = 1; i <= 7; i++) for(int j = 0; j < i; j++) cout << perm[i][j] << " \n"[j + 1 == i];
	int N, M;
	cin >> N >> M;
	cout << compute(N, M) << endl;
}
