#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;
const ll inf = 1e17;

vector<pair<int, ll> > G[10005];

/*int size[10005];
void get_size(int u, int p)
{
	size[u] = 1;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		get_size(v, u);
		size[u] += size[v];
	}
}*/

int N, K;

int start[10005], end[10005];
ll to[10005];
int dfstime; // [0, N]
int order[10005];
void dfs_order(int u, int p)
{
	start[u] = dfstime;
	order[dfstime] = u;
	dfstime++;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		if(v == p) continue;
		to[v] = G[u][i].second;
		dfs_order(v, u);
	}
	end[u] = dfstime;
}

ll dp[10005][22];
ll test(int s)
{
	//printf("=== trying %d ===\n", s);
	dfstime = 0;
	dfs_order(s, -1);
	to[s] = 0;
	order[0] = s;

	for(int i = 0; i < 10005; i++)
		for(int j = 0; j < 22; j++)
			dp[i][j] = inf;

	dp[0][0] = 0; // [cur][#ignored]
	for(int t = 0; t <= N - 1; t++)
	{
		// drop u?
		int u = order[t];
		int size = end[u] - start[u];
		//printf("at %d, size = %d, cost = %d, (from=%d, to=%d)\n", u, size, (int)(to[u]), start[u], end[u]);
		for(int k = 0; k <= K; k++)
			dp[t + 1][k] = min(dp[t + 1][k], dp[t][k] + to[u]);
		for(int k = 0; k <= K - size; k++)
		{
			dp[end[u]][k + size] = min(dp[end[u]][k + size], dp[t][k]);
			//printf("[%d][%d] <- %d\n", end[u], k + size, dp[end[u]][k + size]);
		}
		//for(int k = 0; k <= K; k++)
			//printf("[%d][%d]: %d\n", t + 1, k, (int)(dp[t + 1][k]));
	}
	return dp[N][K];
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--)
	{
		for(int i = 0; i < 10005; i++) G[i].clear();

		cin >> N >> K;
		for(int i = 1; i < N; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;
			u++, v++;
			G[u].push_back(make_pair(v, w));
			G[v].push_back(make_pair(u, w));
		}

		ll best = inf;
		for(int i = 1; i <= 21 && i <= N; i++)
			best = min(best, test(i));

		cout << 2 * best << '\n';
	}
}
