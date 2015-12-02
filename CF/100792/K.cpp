#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 19);

int depth[MAX];
int path[MAX][20]; // [u][d] = jump 2^d steps from u
void add(int u, int p)
{
	depth[u] = depth[p] + 1;
	path[u][0] = p;
	for(int i = 1; i < 20; i++)
		path[u][i] = path[path[u][i - 1]][i - 1];
}
int jump(int v, int d) // jump from v up d nodes
{
	for(int i = 0; i < 20; i++)
		if(d & (1 << i)) v = path[v][i];
	return v;
}
int jump_until(int v, int t) // jump until node <= t
{
	if(v <= t) return v;
	for(int i = 19; i >= 0; i--)
		if(path[v][i] > t)
			v = path[v][i];
	return path[v][0];
}
bool compare(int v, int w) // compare paths from u and v lexicographically
{
	if(depth[v] < depth[w]) return !compare(w, v);
	v = jump(v, depth[v] - depth[w]);
	if(v == w) return true; // w is prefix of v
	int d = depth[v];
	for(int i = 19; i >= 0; i--)
	{
		if((1 << i) > d) continue;
		if(path[v][i] != path[w][i])
			v = path[v][i], w = path[w][i];
	}
	return (v < w);
}

int N, M;
vector<int> G[MAX];

bool vis[MAX];
void dfs(int u)
{
	vis[u] = true;
	int best_from = 0;
	for(int v : G[u])
	{
		if(!vis[v]) dfs(v);
		if(best_from == 0 || compare(v, best_from))
			best_from = v;
	}
	int p = jump_until(best_from, u);
// 	printf("u=%d best=%d p=%d\n", u, best_from, p);
	add(u, p);
}

int ans[MAX];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= M; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
	}
	for(int i = 1; i <= N; i++)
		if(!vis[i]) dfs(i);
	for(int i = 1; i <= N; i++) ans[i] = i;
	sort(ans + 1, ans + 1 + N, compare);
	for(int i = 1; i <= N; i++) cout << ans[i] << ' ';
}
