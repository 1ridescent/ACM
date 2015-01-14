#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int P[305];
int ans[305];
vector<int> G[305];
bool vis[305];
vector<int> cur;
void dfs(int u)
{
	if(vis[u]) return;
	vis[u] = true;
	cur.push_back(u);
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		dfs(v);
	}
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> P[i];
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
		{
			char c;
			cin >> c;
			if(c == '1') G[i].push_back(j);
		}
	memset(vis, 0, sizeof(vis));
	for(int s = 1; s <= N; s++)
	{
		if(vis[s]) continue;
		dfs(s);
		vector<int> cur_vals;
		for(int i = 0; i < cur.size(); i++)
			cur_vals.push_back(P[cur[i]]);
		sort(cur.begin(), cur.end());
		sort(cur_vals.begin(), cur_vals.end());
		for(int i = 0; i < cur.size(); i++)
		{
			ans[cur[i]] = cur_vals[i];
		}
		cur.clear();
		cur_vals.clear();
	}
	for(int i = 1; i <= N; i++) cout << ans[i] << ' ';
}
