#include <bits/stdc++.h>

using namespace std;

int Q[1000005]; // [hd, tl)
int hd, tl;
void init()
{
	hd = tl = 0;
}
void push(int x)
{
	Q[tl++] = x;
}
void pop()
{
	hd++;
}
int front()
{
	return Q[hd];
}
bool empty()
{
	return (hd == tl);
}

int N, M;
vector<int> G[1005];

bool vis[1005];
vector<int> found;
void dfs(int u)
{
	vis[u] = true;
	found.push_back(u);
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(!vis[v]) dfs(v);
	}
}

int dist[1005];
int Try(int s)
{
	memset(dist, -1, sizeof(dist));
	init();
	dist[s] = 0;
	push(s);
	while(!empty())
	{
		int u = front();
		pop();
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if(dist[v] == -1)
			{
				dist[v] = dist[u] + 1;
				push(v);
			}
			else if(dist[v] == dist[u])
				return -1;
		}
	}
	int maxd = 0;
	for(int i = 1; i <= N; i++)
	{
		//if(dist[i] == -1) return -1;
//		cout << dist[i] << ' '; if(i == N) cout << endl;
		maxd = max(maxd, dist[i]);
	}
//	printf("%d %d\n", s, maxd);
	return maxd;
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	int ans = 0;
	for(int i = 1; i <= N; i++)
	{
		if(!vis[i])
		{
			int b = -1;
			dfs(i);
			for(int j = 0; j < found.size(); j++)
			{
				int v = found[j];
				b = max(b, Try(v));
			}
			found.clear();
			if(b == -1)
			{
				cout << "-1\n";
				return 0;
			}
			ans += b;
		}
	}
	cout << ans;
}
