#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> primes;
bool isprime[1000005];
void sieve()
{
	memset(isprime, -1, sizeof(isprime));
	for(int i = 2; i <= 1000000; i++)
		if(isprime[i])
		{
			primes.push_back(i);
			for(int j = i + i; j <= 1000000; j += i)
				isprime[j] = false;
		}
}

map<ll, ll> num;

bool is1prime(unsigned long long x)
{
	for(int i = 0; i < primes.size(); i++)
	{
		ll p = primes[i];
		if(x % p == 0) return false;
		if(p * p > x) return true;
	}
	return true;
}

bool is12prime(unsigned long long x)
{
	for(int i = 0; i < primes.size(); i++)
	{
		ll p = primes[i];
		if(p * p >= x) return true;
		if(x % p == 0)
			return (x / p >= 10000 && is1prime(x / p));
	}
	return true;
}

int main()
{
	ll A;
	cin >> A;
	num[A] = 1;
	sieve();
	//cout << primes.back() << endl;
	for(int p : primes)
	{
		if(p >= 10000) break;
		for(auto it : num)
		{
			for(ll x = p; x < A; x *= p)
			{
				if(it.first % (x + 1) == 0)
					num[it.first / (x + 1)] += it.second;
			}
		}
	}
	ll res = 0;
	for(auto it : num)
	{
		cout << it.first << ' ' << it.second << ' ' << is12prime(it.first) << endl;
		if(it.first == 1 || it.first >= 9999 && is12prime(it.first))
		{
			cout << "add " << it.first << ' ' << it.second << ' ' << is12prime(it.first) << endl;
			res += it.second;
		}
	}
	cout << res;
}
