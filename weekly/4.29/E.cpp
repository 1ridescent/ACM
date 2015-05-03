#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <queue>

using namespace std;

typedef long long ll;
const ll inf = 1e12;

int N, M;
vector<int> G[40040];

queue<pair<int, int> > Q;
bool vis[40040];
void bfs(int s, ll* dist)
{
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= N; i++)
		dist[i] = inf;
	Q.push(make_pair(s, 0));
	while(!Q.empty())
	{
		int u = Q.front().first, d = Q.front().second;
		Q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		dist[u] = d;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			Q.push(make_pair(v, d + 1));
		}
	}
}

ll B, E, P;
ll distB[40040], distE[40040], distN[40040];

int main()
{
	cin >> B >> E >> P >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bfs(1, distB);
	bfs(2, distE);
	bfs(N, distN);
	ll best = inf;
	for(int i = 1; i <= N; i++)
		best = min(best, distB[i] * B + distE[i] * E + distN[i] * P);
	cout << best << endl;
}
