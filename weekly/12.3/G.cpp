#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
const ll inf = 1e17;

int N;

vector<ll> U[1000100];

int I[1000100];

vector<ll> V[1000100];

bool cmp(int a, int b)
{
	return U[a].size() < U[b].size();
}

int main()
{
	ios::sync_with_stdio(false);

	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int s;
		cin >> s;
		for(int j = 0; j < s; j++)
		{
			ll x;
			cin >> x;
			U[i].push_back(x);
		}
	}

	for(int i = 0; i < N; i++) I[i] = i;
	sort(I, I + N, cmp);

	for(int i = 0; i < N; i++)
		V[i] = U[I[i]];

	ll total = 0;
	ll ans = -inf;

	ll last = 0;
	for(int s = 0; s < N; )
	{
		int t = s;
		while(t < N && V[t].size() == V[s].size()) t++;

		ll best = -inf;
		for(int i = s; i < t; i++)
		{
			ll sum = 0;
			for(int j = last; j < V[i].size(); j++)
				sum += V[i][j];
			best = max(best, sum);
		}

		//cout << s << ' ' << t << ' ' << best << endl;

		total += best;
		ans = max(ans, total);

		last = V[s].size();
		s = t;
	}
	cout << ans << '\n';
}
