#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = 100100;
const int INF = 100000000;

struct SCC
{
	int N, cnt, cmpt;
	int num[MAX], low[MAX], ans[MAX];
	vector<int> G[MAX];
	vector<int> S; // stack
	bool on_stack[MAX];

	void reset()
	{
		for(int i = 0; i < MAX; i++) G[i].clear();
	}
	void strong(int u)
	{
		if(num[u] != 0) return;
		num[u] = low[u] = ++cnt;
		S.push_back(u);
		on_stack[u] = true;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			strong(v);
		}
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if(on_stack[v]) low[u] = min(low[u], low[v]);
		}
		if(num[u] == low[u])
		{
			while(!S.empty())
			{
				int x = S.back();
				S.pop_back();
				on_stack[x] = false;
				ans[x] = cmpt;
				if(x == u) break;
			}
			cmpt++;
		}
	}
	void scc()
	{
		memset(num, 0, sizeof(num));
		memset(low, 0, sizeof(low));
		memset(ans, 0, sizeof(ans));
		memset(on_stack, 0, sizeof(on_stack));
		S.clear();
		cnt = 0;
		cmpt = 0;
		for(int i = 1; i <= N; i++) strong(i);
	}
};

SCC G;
int M;
int E[MAX][2];
int num[MAX];
vector<int> out[MAX], in[MAX];

int num_out[MAX], num_in[MAX];

bool vis[MAX];
int dfs_out(int u)
{
	if(vis[u]) return num_out[u];
	vis[u] = true;
	num_out[u] = -INF;
	for(int i = 0; i < in[u].size(); i++)
	{
		int v = in[u][i];
		int n = dfs_out(v);
		if(n >= 0)
		{
			//printf("update num[%d] to be %d + %d\n", u, n, num[u]);
			num_out[u] = max(num_out[u], n + num[u]);
		}
	}
	//printf("num[%d] = %d, num_out[%d] = %d\n", u, num[u], u, num_out[u]);
	return num_out[u];
}
int dfs_in(int u)
{
	if(vis[u]) return num_in[u];
	vis[u] = true;
	num_in[u] = -INF;
	for(int i = 0; i < out[u].size(); i++)
	{
		int v = out[u][i];
		//printf("edge %d->%d\n", u, v);
		int n = dfs_in(v);
		if(n >= 0)
			num_in[u] = max(num_in[u], n + num[u]);
	}
	//printf("num_in[%d] = %d\n", u, num_in[u]);
	return num_in[u];
}

int main()
{
	freopen("grass.in", "r", stdin);	freopen("grass.out", "w", stdout);
	cin >> G.N >> M;
	for(int i = 0; i < M; i++)
	{
		cin >> E[i][0] >> E[i][1];
		G.G[E[i][0]].push_back(E[i][1]);
	}
	G.scc();
	for(int i = 1; i <= G.N; i++)
	{
		//cout << G.ans[i] << " \n"[i == G.N];
		num[G.ans[i]]++;
	}
	for(int i = 0; i < M; i++)
	{
		if(G.ans[E[i][0]] != G.ans[E[i][1]])
		{
			out[G.ans[E[i][0]]].push_back(G.ans[E[i][1]]);
			in[G.ans[E[i][1]]].push_back(G.ans[E[i][0]]);
		}
	}
	num_out[G.ans[1]] = num_in[G.ans[1]] = 0;
	memset(vis, 0, sizeof(vis));
	vis[G.ans[1]] = true;
	for(int i = 0; i < G.cmpt; i++) dfs_out(i);
	memset(vis, 0, sizeof(vis));
	vis[G.ans[1]] = true;
	for(int i = 0; i < G.cmpt; i++) dfs_in(i);
	int ans = num[G.ans[1]];
	for(int i = 0; i < M; i++)
	{
		//printf("trying (%d)->(%d)\n", G.ans[E[i][0]], G.ans[E[i][1]]);
		ans = max(ans, num[G.ans[1]] + num_out[G.ans[E[i][1]]] + num_in[G.ans[E[i][0]]]);
	}
	cout << ans << '\n';
}
