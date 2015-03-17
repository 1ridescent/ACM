#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		ll x;
		cin >> x;
		ll s = 0;
		ll p = x;
		for(ll i = 1; i * i < x; i++)
		{
			ll p2 = x / (i + 1);
			s += (p - p2) * i;
			p = p2;
		}
		for(; p >= 1; p--)
			s += x / p;
		cout << s % 1000000 << '\n';
	}
}
