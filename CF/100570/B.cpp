#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef long long ll;

int N, M;
vector<int> G[100005], E[100005], C[100005];

ll dist[100005];
int color[100005];
priority_queue<pair<ll, pair<int, int> > > Q; // (d, v, c)

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	int cc;
	cin >> cc;
	for(int i = 0; i < M; i++)
	{
		int a, b, e, c;
		cin >> a >> b >> e >> c;
		G[a].push_back(b);
		E[a].push_back(e);
		C[a].push_back(c);
	}

	int s;
	cin >> s;
	Q.push(make_pair(0, make_pair(s, 0)));
	memset(color, -1, sizeof(color));
	memset(dist, -1, sizeof(dist));
	while(!Q.empty())
	{
		ll d = -Q.top().first;
		int u = Q.top().second.first, c = Q.top().second.second;
		Q.pop();
		if(color[u] == -2) continue;
		else if(color[u] == -1) // unvisited
		{
			dist[u] = d;
			for(int i = 0; i < G[u].size(); i++)
			{
				int v = G[u][i], e = E[u][i], c2 = C[u][i];
				if(c == c2) continue;
				Q.push(make_pair(-(d + e), make_pair(v, c2)));
			}
			color[u] = c;
		}
		else if(color[u] == c) continue;
		else
		{
			for(int i = 0; i < G[u].size(); i++)
			{
				int v = G[u][i], e = E[u][i], c2 = C[u][i];
				if(c == c2) continue;
				Q.push(make_pair(-(d + e), make_pair(v, c2)));
			}
			color[u] = -2;
		}
	}

	int Q;
	cin >> Q;
	while(Q--)
	{
		int t;
		cin >> t;
		cout << dist[t] << '\n';
	}
}
