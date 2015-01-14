#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

struct Euclid
{
	ll x, y, q;
	void euclid(ll a, ll b)
	{
		if(b == 0) x = 1, y = 0, q = a;
		else
		{
			euclid(b, a % b);
			ll temp = x;
			x = y;
			y = temp - a / b * y;
		}
	}
};
int mod_inverse(int a, int m)
{
	Euclid E;
	E.euclid(a, m);
	return (E.x + m) % m;
}
pair<ll, ll> convert(int n)
{
	if(n < 0) return make_pair(0, -n);
	return make_pair(n, 0);
}

ll X, Y, P, K;

int main()
{
	cin >> X >> Y >> P >> K;
	for(ll x = -100000; x <= 100000; x++) // number of +X
	{
		if(abs(x) > K) continue;
		ll diff = P - (x * X);
		if(diff % Y == 0)
		{
			int y = diff / Y;
			ll total = abs(x) + abs(y);
			assert(x * X + y * Y == P);
			int extra = K - total;
			if(total <= K && extra % 2 == 0)
			{
				cout << "YES\n" << convert(x).first + extra / 2 << ' ' << convert(x).second + extra/  2 << ' ' << convert(y).first << ' ' << convert(y).second << endl;
				return 0;
			}
		}
	}
	cout << "NO\n";
}
