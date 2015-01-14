#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

int N;

vector<ll> V[1000100];

bool is_size[1000100];

ll best[1000100];

vector<ll> lens;

int main()
{
	ios::sync_with_stdio(false);

	memset(is_size, 0, sizeof(is_size));

	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int s;
		cin >> s;
		for(int j = 0; j < s; j++)
		{
			ll x;
			cin >> x;
			V[i].push_back(x);
		}

		is_size[V[i].size()] = true;
	}

	for(int i = 0; i < 1000100; i++) best[i] = -inf;
	for(int i = 0; i < N; i++)
	{
		ll cur = 0;
		for(int j = 0; j < V[i].size(); j++)
		{
			cur += V[i][j];
			if(is_size[j + 1])
			{
				best[j + 1] = max(best[j + 1], cur);
				cur = 0;
			}
		}
	}

	ll cur = 0;
	ll ans = -inf;
	for(int i = 0; i < 1000100; i++)
	{
		if(is_size[i])
		{
			//cout << i << ": " << best[i] << endl;
			cur += best[i];
			ans = max(ans, cur);
		}
	}
	cout << ans << '\n';
}
