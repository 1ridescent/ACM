#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

const int INF = 10000000;

vector<pair<int, int> > G[300000];

int N, M;
int S, T;

void add_edge(int u, int v, int w)
{
	G[u].push_back(make_pair(v, w));
	G[v].push_back(make_pair(u, w));
	//cout << u << ' ' << v << ' '<< w << endl;
}

bool vis[300000];
priority_queue<pair<int, int> > Q;
int dijkstra()
{
	memset(vis, 0, sizeof(vis));
	Q.push(make_pair(0, S));
	while(!Q.empty())
	{
		int u = Q.top().second, d = -Q.top().first;
		Q.pop();
		//cout << u << ": " << d << endl;
		if(vis[u]) continue;
		if(u == T) return d;
		vis[u] = true;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].first, w = G[u][i].second;
			Q.push(make_pair(-(d + w), v));
		}
	}
	return -1;
}

int main()
{
	cin >> N >> M;
	S = (N * (M + 1) + M), T = 0;
	for(int r = 0; r < N; r++)
	{
		string s;
		cin >> s;
		for(int c = 0; c < M; c++)
		{
			int a = r * (M + 1) + c;
			int b = r * (M + 1) + (c + 1);
			int cc = (r + 1) * (M + 1) + (c + 1);
			int d = (r + 1) * (M + 1) + c;
			char k = s[c];

			int u, v;
			if(k == '/') u = 1, v = 0;
			else u = 0, v = 1;
			add_edge(a, cc, u);
			add_edge(b, d, v);
		}
	}

	int res = dijkstra();
	if(res == -1) cout << "NO SOLUTION\n";
	else cout << res << endl;
}
