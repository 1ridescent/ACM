#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define MOD(x) ((x) % mod)

ll power(ll b, ll e)
{
	if(e == 0) return 1;
	ll res = power(b, e / 2);
	res = (res * res) % mod;
	if(e % 2 == 1) res = (res * b) % mod;
	return res;
}
ll inv(ll x)
{
	return power(x, mod - 2);
}

ll fact[1000];
ll invfact[1000];
void precompute()
{
	fact[0] = 1;
	for(int i = 1; i < 1000; i++) fact[i] = MOD(fact[i - 1] * i);
	for(int i = 0; i < 1000; i++) invfact[i] = inv(fact[i]);
}

ll choose(ll n, ll k)
{
	return MOD(fact[n] * MOD(invfact[n - k] * invfact[k]));
}

int N, S;
int A[33];
ll dp[33][1000];

int main()
{
	precompute();
	memset(dp, 0, sizeof(dp));

	cin >> N;
	dp[0][0] = 1; // [num NOT in PIE][sum]
	S = 0;
	for(int t = 1; t <= N; t++)
	{
		int a;
		cin >> a;
		S += a;
		for(int n = t; n >= 1; n--)
		{
			for(int s = S; s >= a; s--)
			{
				dp[n][s] += dp[n - 1][s - a] * invfact[a];
				dp[n][s] %= mod;
				cout << t << ": " << n << ' ' << s << " : " << dp[n][s] << " <- " << n - 1 << ' ' << s - a << " : " << dp[n - 1][s - a] << endl;
			}
		}
	}

	//while(true){int n,s;cin>>n>>s;cout<<dp[n][s]<<endl;}

	ll res = 0;
	for(int n = 0; n <= N; n++) // num in PIE
	{
		ll sign = power(mod - 1, n);
		for(int s = 0; s <= S; s++) // in sum
		{
			res += MOD(sign * MOD(choose(S, s) * MOD(fact[S - s] * dp[N - n][S - s])));
			res += sign * ((fact[S - s] * dp[N - n][s]) % mod);
			res %= mod;
		}
	}

	cout << res << endl;
}
