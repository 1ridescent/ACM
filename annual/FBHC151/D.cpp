#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;

const int inf = 1e9;

int N;
vector<int> G[200005];

int dp[200005][22];

void calc(int u)
{
	//cout << "at " << u << endl;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		calc(v);
	}
	memset(dp[u], 0, sizeof(dp[u]));
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		int best = inf, bestk = -1;
		for(int k = 1; k <= 20; k++)
		{
			if(dp[v][k] < best)
				best = dp[v][k], bestk = k;
		}
		for(int k = 1; k <= 20; k++)
			if(k != bestk)
				dp[u][k] += best;
		int best2 = inf, bestk2 = -1;
		for(int k = 1; k <= 20; k++)
		{
			if(k == bestk) continue;
			if(dp[v][k] < best2)
				best2 = dp[v][k], bestk2 = k;
		}
		//assert(bestk != bestk2);
		dp[u][bestk] += best2;
	}
	for(int k = 1; k <= 20; k++)
		dp[u][k] += k;
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cin >> N;
		for(int i = 0; i <= 200002; i++)
			G[i].clear();
		for(int i = 1; i <= N; i++)
		{
			int p;
			cin >> p;
			if(p > 0) G[p].push_back(i);
		}
		calc(1);
		int res = inf;
		for(int k = 1; k <= 20; k++)
			res = min(res, dp[1][k]);
		cout << "Case #" << t << ": " << res << '\n';
	}
}
