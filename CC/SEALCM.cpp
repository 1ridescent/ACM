#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
ll add(ll a, ll b)
{
	return (a + b) % mod;
}
ll sub(ll a, ll b)
{
	return (a - b + mod) % mod;
}
ll mul(ll a, ll b)
{
	return ((long long)a * b) % mod;
}

ll power(ll b, ll e)
{
	if(e == 0) return 1;
	ll r = power(b, e / 2);
	r = mul(r, r);
	if(e % 2) r = mul(r, b);
	return r;
}

vector<ll> primes;
vector<pair<ll, ll> > factors[1005];
void precompute()
{
	for(ll i = 2; i <= 1000; i++)
		for(ll j = 2; j <= i; j++)
		{
			if(j == i) primes.push_back(j);
			if(i % j == 0) break;
		}
	for(ll i = 1; i <= 1000; i++)
	{
		ll x = i;
		for(ll j = 0; j < primes.size(); j++)
		{
			ll p = primes[j];
			if(x % p == 0)
			{
				ll f = 1;
				while(x % p == 0) x /= p, f *= p;
				factors[i].push_back(make_pair(p, f));
			}
		}
	}
}

ll N, L, R, M;

ll powerN[1005];
void compute_powers()
{
	for(ll i = 0; i <= 1000; i++)
		powerN[i] = power(i, N);
}

ll compute(ll d)
{
	ll res = 0;
	for(ll b = 0; b < (1 << factors[d].size()); b++)
	{
		ll f = 1;
		for(ll i = 0; i < factors[d].size(); i++)
			if(b & (1 << i))
				f *= factors[d][i].second;
		ll val = powerN[M - M / f];
		//cout << d << ' ' << b << ' ' << val << endl;
		if(__builtin_popcount(b) % 2) res = sub(res, val);
		else res = add(res, val);
	}
	//cout << d << ' ' << add(powerN[M], res) << endl;
	return add(powerN[M], res);
}

int main()
{
	precompute();
	ll T;
	cin >> T;
	while(T--)
	{
		cin >> N >> M >> L >> R;
		compute_powers();
		ll res = 0;
		for(ll i = L; i <= R; i++)
			res = add(res, compute(i));
		cout << res << '\n';
	}
}
