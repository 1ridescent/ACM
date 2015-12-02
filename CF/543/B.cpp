#include <bits/stdc++.h>

using namespace std;

vector<int> G[3005];

int N, M;

queue<int> Q;
void bfs(int s, int* dist)
{
	for(int i = 1; i <= N; i++)
		dist[i] = -1;
	dist[s] = 0;
	Q.push(s);
	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		int d = dist[u];
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if(dist[v] == -1)
			{
				dist[v] = d + 1;
				Q.push(v);
			}
		}
	}
}
int dist[3005][3005];

int main()
{
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int s = 1; s <= N; s++)
		bfs(s, dist[s]);
	int s1, t1, l1, s2, t2, l2;
	cin >> s1 >> t1 >> l1 >> s2 >> t2 >> l2;
	if(dist[s1][t1] > l1 || dist[s2][t2] > l2)
	{
		cout << "-1\n";
		return 0;
	}
	int best = dist[s1][t1] + dist[s2][t2];
	for(int a = 1; a <= N; a++)
		for(int b = 1; b <= N; b++)
		{
			if(dist[s1][a] + dist[a][b] + dist[b][t1] <= l1 &&
					dist[s2][a] + dist[a][b] + dist[b][t2] <= l2)
				best = min(best, dist[s1][a] + dist[s2][a] + dist[a][b] + dist[b][t1] + dist[b][t2]);
		}
	swap(s1, t1);
	for(int a = 1; a <= N; a++)
		for(int b = 1; b <= N; b++)
		{
			if(dist[s1][a] + dist[a][b] + dist[b][t1] <= l1 &&
					dist[s2][a] + dist[a][b] + dist[b][t2] <= l2)
				best = min(best, dist[s1][a] + dist[s2][a] + dist[a][b] + dist[b][t1] + dist[b][t2]);
		}
	cout << M - best << endl;
}

