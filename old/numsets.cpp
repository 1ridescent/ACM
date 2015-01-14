#include <iostream>
#include <vector>

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

ll num(int n, int k)
{
	ll res = 1;
	for(int i = 0; i < k; i++)
	{
		res = MOD(res * ((1<<n) - (1<<i)));
		res = MOD(res * inv(i+1));
	}
	return res;
}
ll totalnum(int n)
{
	ll res = 0;
	for(int k = 0; k < n; k++)
	{
		res = MOD(res + MOD(num(n, k) * inv(num(k, k))));
	}
	return res;
}
ll compute(int k)
{
	if(k == 0) return 1;
	int highbit;
	for(int i = 0; i <= 30; i++) if(k & (1<<i)) highbit = i;
	return MOD( 2 * compute(k - (1<<highbit)) + totalnum(highbit) );
}

int main()
{
	int K;
	cin >> K;
	cout << totalnum(K) << endl; return 0;
	cout << compute(K) << endl;
	return 0;
}
