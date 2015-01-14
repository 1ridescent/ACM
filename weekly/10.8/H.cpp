#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int inf = 1000000000;

int N, K;
vector<int> G[100005];
int W[100005];
int start[100005], end[100005];

int dfstime;
int leaves;
void dfs(int u)
{
	start[u] = dfstime++;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		dfs(v);
	}
	if(G[u].empty()) leaves++;
	end[u] = dfstime;
}

int dp[2][100005];

int main()
{
	while(true)
	{
		scanf("%d %d", &N, &K);
		if(!N) break;
		for(int i = 1; i <= N; i++)
		{
			int p, w;
			scanf("%d %d", &p, &w);
			G[p].push_back(i);
			W[i] = w;
		}
		dfstime = 0;
		leaves = 0;
		dfs(G[0][0]);

		/*if(K > leaves)
		{
			printf("0\n");
		}
		else*/
		{
			//for(int i = 1; i <= N; i++) cout << start[i] << ' ' << end[i] << endl;

			memset(dp[0], 0, sizeof(dp[0]));
			for(int k = 1; k <= K; k++)
			{
				int s = (k + 1) % 2, t = (k % 2);
				for(int i = 0; i <= N; i++)
					dp[t][i] = -inf;
				for(int u = 1; u <= N; u++)
				{
					dp[t][end[u]] = max(dp[t][end[u]], dp[s][start[u]] + W[u]);
				}
				for(int i = 1; i <= N; i++)
					dp[t][i] = max(dp[t][i], dp[t][i - 1]);
				/*cout << k << " : ";
				for(int i = 1; i <= N; i++) cout << dp[t][i] << ' ';
				cout << endl;*/
			}
			int best = 0;
			for(int i = 0; i <= N; i++)
				best = max(best, dp[K % 2][i]);
			printf("%d\n", best);
		}

		for(int i = 0; i <= N; i++) G[i].clear();
	}
}
