#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>

using namespace std;

int N, M;
vector<int> G[100005];
int A[100005];

bool visited[100005];
void flood(int u)
{
	visited[u] = true;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(visited[v]) continue;
		flood(v);
	}
}

vector<int> T[100005]; // tree
void make_tree(int u)
{
	visited[u] = true;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(visited[v]) continue;
		T[u].push_back(v);
		make_tree(v);
	}
}

vector<int> path;
int dfs_tree(int u)
{
	bool res = 1;
	path.push_back(u);
	for(int i = 0; i < T[u].size(); i++)
	{
		int v = T[u][i];
		int b = dfs_tree(v);
		if(b != A[v])
		{
			path.push_back(u);
			path.push_back(v);
			res ^= 1;
		}
		res ^= 1;
		path.push_back(u);
	}
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i = 1; i <= N; i++) cin >> A[i];

	int start = -1;
	memset(visited, 0, sizeof(visited));
	for(int u = 1; u <= N; u++)
	{
		if(visited[u]) continue;
		if(A[u])
		{
			if(start != -1)
			{
				cout << -1;
				return 0;
			}
			start = u;
			flood(u);
		}
	}
	if(start == -1)
	{
		cout << 0;
		return 0;
	}

	memset(visited, 0, sizeof(visited));
	make_tree(start);

	int b = dfs_tree(start);
	if(b != A[start]) path.pop_back();

	cout << path.size() << endl;
	for(int i = 0; i < path.size(); i++) cout << path[i] << ' ';
}
