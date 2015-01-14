#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

int N, M;
vector<int> G[10050];
ll money[10050];
bool visited[10050];
ll dfs(int u)
{
	visited[u] = true;
	ll res = money[u];
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(visited[v]) continue;
		res += dfs(v);
	}
	//cout << u << ' ' << res<<endl;
	return res;
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < N; i++) cin >> money[i];
	memset(visited, 0, sizeof(visited));
	for(int i = 0; i < M; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i = 0; i < N; i++)
	{
		if(visited[i]) continue;
		if(dfs(i) != 0)
		{
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	}
	cout << "POSSIBLE\n";
}
