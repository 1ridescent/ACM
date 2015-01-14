#include <iostream>

using namespace std;

typedef long long ll;

const ll mod = 1000000007;
#define MOD(x) ((x) % mod)

ll power(ll x, ll e)
{
    if(e == 0) return 1;
    ll res = power(x, e/2);
    res = MOD(res * res);
    if(e % 2) res = MOD(res * x);
    return res;
}
ll inv(ll x)
{
    return power(x, mod-2);
}
const int MAX = (1 << 21);
ll fact[MAX];
ll invfact[MAX];
ll derangements[MAX];
void pre()
{
    fact[0] = 1;
    for(int i = 1; i < MAX; i++) fact[i] = MOD(fact[i-1] * i);
    for(int i = 0; i < MAX; i++) invfact[i] = inv(fact[i]);
    derangements[0] = 1;
    for(int i = 1; i < MAX; i++)
    {
    	derangements[i] = MOD(i*derangements[i-1] + ((i%2) ? -1 : 1) + mod);
    }
}

int main()
{
	pre();
	int T;
	cin >> T;
	for(int t = 0; t < T; t++)
	{
		int N, K;
		cin >> N >> K;

		// edge cases
		if(K == 1)
		{
			cout << 0 << endl;
			continue;
		}
		if(N == 2 && K == 2)
		{
			cout << 1 << endl;
			continue;
		}
		else if(N <= 2)
		{
			cout << 0 << endl;
			continue;
		}

		ll cur = 1;
		ll total = 0;
		for(int i = 1; i*K <= N; i++)
		{
			cur = MOD(cur * MOD(fact[N-(i-1)*K] * invfact[N-i*K]));
			cur = MOD(cur * invfact[K]);
			cur = MOD(cur * fact[K-1]);
			total = MOD(total + ((i%2) ? 1 : -1) * MOD( MOD(cur * invfact[i]) * derangements[N-i*K]) + mod);
			//cout << total << ' ';
		}
		cout << total << endl;
	}
}
