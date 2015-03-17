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

ll fact[333333];
ll invfact[333333];
void pre()
{
	fact[0] = invfact[0] = 1;
	for(int i = 1; i < 333333; i++)
	{
		fact[i] = (i * fact[i - 1]) % mod;
		invfact[i] = inv(fact[i]);
	}
}
ll choose(int n, int k)
{
	return (fact[n] * ((invfact[n - k] * invfact[k]) % mod)) % mod;
}
ll compute(int n, int m)
{
	//cout << n + m << ' ' << m << " -> " << choose(n + m, n) << endl;
	return choose(n + m, n);
}

int N, M, K;
int X[1005], Y[1005];
bool vis[1005];
ll dp[1005];

ll calc(int i)
{
	if(vis[i]) return dp[i];
	int n = X[i], m = Y[i];
	ll bad = 0;
	for(int j = 0; j < K; j++)
	{
		int x = X[j], y = Y[j];
		if(j != i && x <= n && y <= m)
		{
			bad = (bad + calc(j) * compute(n - x, m - y)) % mod;
		}
	}
	vis[i] = true;
	dp[i] = (compute(n - 1, m - 1) - bad + mod) % mod;
	//cout << i << " : n=" << n << " m=" << m << "  bad = " << bad << " , res = " << dp[i] << endl;
	return dp[i];
}

int main2()
{
	memset(vis, 0, sizeof(vis));
	cin >> N >> M >> K;
	for(int i = 0; i < K; i++)
	{
		cin >> X[i] >> Y[i];
		if(X[i] == N && Y[i] == M)
		{
			cout << 0 << endl;
			return 0;
		}
	}
	X[K] = N, Y[K] = M;
	K++;
	cout << calc(K - 1) << endl;
	return 0;
}

int main()
{
	pre();
	int T;
	cin >> T;
	while(T--) main2();
}
