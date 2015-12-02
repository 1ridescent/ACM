#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> primes;
void sieve()
{
	bool isprime[1000005];
	memset(isprime, -1, sizeof(isprime));
	for(int i = 2; i <= 1000001; i++)
		if(isprime[i])
		{
			primes.push_back(i);
			for(int j = i + i; j <= 1000001; j += i)
				isprime[j] = false;
		}
}

map<ll, ll> num;

bool isprime(unsigned long long x)
{
	for(int i = 0; i < primes.size(); i++)
	{
		ll p = primes[i];
		if(x % p == 0) return false;
		if(p * p > x) return true;
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
		cout << it.first << ' ' << it.second << ' ' << isprime(it.first) << endl;
		if(it.first == 1 || it.first >= 999994 && isprime(it.first - 1))
		{
			cout << "add " << it.first << ' ' << it.second << ' ' << isprime(it.first) << endl;
			res += it.second;
		}
	}
	cout << res;
}
