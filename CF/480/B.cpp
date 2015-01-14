#include <iostream>
#include <set>

using namespace std;

typedef long long ll;

set<ll> S;

ll N, L, X, Y;

bool distance(ll d)
{
	for(set<ll>::iterator it = S.begin(); it != S.end(); it++)
	{
		ll x = *it;
		if(S.count(x + d)) return true;
	}
	return false;
}

int main()
{
	cin >> N >> L >> X >> Y;
	for(int i = 0; i < N; i++)
	{
		ll x;
		cin >> x;
		S.insert(x);
	}

	if(distance(X) && distance(Y))
		cout << 0;
	else if(distance(X))
		cout << 1 << endl << Y;
	else if(distance(Y))
		cout << 1 << endl << X;
	else
	{
		for(set<ll>::iterator it = S.begin(); it != S.end(); it++)
		{
			ll x = *it;
			if(S.count(x + X + Y))
			{
				cout << 1 << endl << x + X;
				return 0;
			}
			if(S.count(x + Y - X))
			{
				if(x - X >= 0)
				{
					cout << 1 << endl << x - X;
					return 0;
				}
				else if(x + Y <= L)
				{
					cout << 1 << endl << x + Y;
					return 0;
				}
			}
		}
		cout << 2 << endl << X << ' ' << Y;
	}
}
