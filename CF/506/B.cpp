#include <iostream>
#include <set>
#include <cstring>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int N, M;
vector<int> G[100005];
vector<int> out[100005];
vector<int> in[100005];

vector<int> cur;
bool vis[100005];
void dfs(int u)
{
	vis[u] = true;
	cur.push_back(u);
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(!vis[v]) dfs(v);
	}
}
int ans = 0;
map<int, int> alive;
vector<int> ready;
void process()
{
	if(cur.empty()) return;
	for(int i = 0; i < cur.size(); i++)
	{
		int u = cur[i];
		alive[u] = in[u].size();
		if(alive[u] == 0)
			ready.push_back(u);
	}
	while(!ready.empty())
	{
		int u = ready.back();
		ready.pop_back();
		alive.erase(u);
		for(int i = 0; i < out[u].size(); i++)
		{
			int v = out[u][i];
			alive[v]--;
			if(alive[v] == 0)
				ready.push_back(v);
		}
	}
	if(alive.empty()) ans += cur.size() - 1;
	else ans += cur.size();
	cur.clear();
	alive.clear();
	ready.clear();
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		out[a].push_back(b);
		in[b].push_back(a);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i = 1; i <= N; i++)
		if(!vis[i])
		{
			dfs(i);
			process();
		}
	cout << ans;
}
