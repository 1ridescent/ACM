#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e15;

int sign(int i)
{
	return (i ? 1 : -1);
}

int N, K;

pair<ll, ll> alive[205][2], dead[205][2];

int main()
{
	for(int i = 0; i < 205; i++) alive[i][0] = alive[i][1] = dead[i][0] = dead[i][1] = make_pair(-inf, 0);
	dead[0][0] = dead[0][1] = make_pair(0, 0);
	cin >> N >> K;
	for(int t = 0; t < N; t++)
	{
		ll x;
		cin >> x;

		// start first seg
		for(int b = 0; b < 2; b++)
			if(0 + sign(b) * x > alive[1][b].first + sign(b) * alive[1][b].second)
				alive[1][b] = make_pair(0, x);

		// new seg from dead / add cur val
		for(int k = K; k >= 1; k--)
		{
			for(int a = 0; a < 2; a++)
				for(int b = 0; b < 2; b++)
				{
					if(alive[k][a].first + sign(b) * (alive[k][a].second + x) > alive[k][b].first + sign(b) * alive[k][b].second)
						alive[k][b] = make_pair(alive[k][a].first, alive[k][a].second + x);
					if(dead[k - 1][a].first + sign(b) * (x - dead[k - 1][a].second) > alive[k][b].first + sign(b) * alive[k][b].second)
						alive[k][b] = make_pair(dead[k - 1][a].first, sign(a) * (x - dead[k - 1][a].second));
				}
		}

		// end seg
		for(int k = K; k >= 0; k--)
		{
			for(int a = 0; a < 2; a++)
				for(int b = 0; b < 2; b++)
					if(alive[k][a].first + sign(b) * alive[k][a].second > dead[k][b].first + sign(b) * dead[k][b].second)
						dead[k][b] = make_pair()
		}

	cout << max(dead[K][0].first, dead[K][1].first);
}
