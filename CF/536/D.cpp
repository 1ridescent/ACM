#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
vector<pair<int, ll> > G[2005];
ll P[2005];

ll start[2];
ll dist[2][2005];
void dijkstra(ll s, ll* ds)
{
	priority_queue<pair<ll, int> > Q;
	Q.push(make_pair(-0, s));
	bool vis[2005];
	memset(vis, 0, sizeof(vis));
	while(!Q.empty())
	{
		int u = Q.top().second;
		ll d = -Q.top().first;
		Q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		ds[u] = d;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].first;
			ll w = G[u][i].second;
			Q.push(make_pair(-(d + w), v));
		}
	}
}

vector<int> take[2][2005];
int num[2];
int to[2][2005][2005];
ll score[2][2005][2005];

ll best[2][2005][2005]; // [player][that player's current][other player's current] = (that player's score) - (other player's score)
ll opt[2][2005][2005]; // [t][a][b] = max_{i = a..num[t]} [ (sum t's scores i..num[t]) + -1 * best[!t][b][i] ]

int main()
{
	cin >> N >> M;
	cin >> start[0] >> start[1];
	for(int i = 1; i <= N; i++) cin >> P[i];
	for(int i = 0; i < M; i++)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
	dijkstra(start[0], dist[0]);
	for(int i = 1; i <= N; i++) printf("dist[0][%d] = %d\n", i, (int)dist[0][i]);
	dijkstra(start[1], dist[1]);
	for(int t = 0; t < 2; t++)
	{
		map<ll, int> id;
		for(int i = 1; i <= N; i++)
			id[dist[t][i]] = -1;
		num[t] = 0;
		for(map<ll, int>::iterator it = id.begin(); it != id.end(); it++)
			it->second = ++num[t];
		for(int i = 1; i <= N; i++)
			dist[t][i] = id[dist[t][i]];
		for(int i = 1; i <= N; i++)
			take[t][dist[t][i]].push_back(i);
		/*for(int i = num[t]; i >= 0; i--)
		{
			score[t][i] = score[t][i + 1];
			for(int j = 0; j < take[t][i].size(); j++)
			{
				//printf("score[%d][%d] += P[%d]=%d\n",t,i,take[t][i][j],(int)P[take[t][i][j]]);
				score[t][i] += P[take[t][i][j]];
			}
			printf("score[%d][%d] = %d\n", t, i, (int)score[t][i]);
		}*/
	}
	for(int a = 0; a < 2; a++) // a's turn
	{
		int b = !a;
		int good[2005];
		ll scores[2005];
		memset(good, 0, sizeof(good));
		memset(scores, 0, sizeof(scores));
		for(int i = 1; i <= N; i++)
		{
			good[dist[a][i]]++;
			scores[dist[a][i]] += P[i];
		}
		for(int j = 0; j <= num[b]; j++)
		{
			for(int i = 0; i < take[b][j].size(); i++)
			{
				good[dist[a][take[b][j][i]]]--;
				scores[dist[a][take[b][j][i]]] -= P[take[b][j][i]];
			}
			int last = num[a] + 1;
			ll s = 0;
			for(int i = num[a]; i >= 0; i--)
			{
				to[a][i][j] = last; // to[player][that player's current][other player's current]
				score[a][i][j] = s;
				if(good[i])
				{
					last = i;
					s += scores[i];
				}
			}
		}
	}
	int p[2];
	for(int s = num[0] + num[1]; s >= 0; s--)
	{
		for(p[0] = 0, p[1] = s; p[1] >= 0; p[0]++, p[1]--)
		{
			if(p[0] > num[0] || p[1] > num[1]) continue;
			for(int t = 0; t < 2; t++)
			{
				int a = p[t], b = p[!t];
				if(to[t][a][b] <= num[t]) best[t][a][b] = score[to[t][a][b]][a][b] - score[t][a][b];
				else best[t][a][b] = opt[t][a + 1][b] - score[t][a][b];
				printf("best[%d][%d][%d] = %d\n", t, a, b, (int)best[t][a][b]);
			}
		}
		for(p[0] = 0, p[1] = s; p[1] >= 0; p[0]++, p[1]--)
		{
			if(p[0] > num[0] || p[1] > num[1]) continue;
			for(int t = 0; t < 2; t++)
			{
				int a = p[t], b = p[!t];
				if(a == num[t]) opt[t][a][b] = score[t][a][b] - best[!t][b][a];
				else opt[t][a][b] = max(score[t][a][b] - best[!t][b][a], opt[t][a + 1][b]);
				printf("opt[%d][%d][%d] = %d\n", t, a, b, (int)opt[t][a][b]);
			}
		}
	}
	ll res = best[0][0][0];
	cout << res << endl;
	if(res == 0) cout << "Flowers";
	else if(res > 0) cout << "Break a heart";
	else cout << "Cry";
}
