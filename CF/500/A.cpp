#include <iostream>
#include <cstring>

using namespace std;

int T, N;
int G[100100];
bool vis[100100];

void dfs(int u)
{
	if(vis[u]) return;
	vis[u] = true;
	//cout << u << ' ' << G[u] << endl;
	if(u < N) dfs(G[u]);
}

int main()
{
	cin >> N >> T;
	for(int i = 1; i < N; i++)
	{
		int x;
		cin >> x;
		G[i] = i + x;
	}
	memset(vis, 0, sizeof(vis));
	dfs(1);
	//for(int i = 1; i <= N; i++) cout << vis[i]; cout << endl;
	cout << (vis[T] ? "YES\n" : "NO\n");
}
