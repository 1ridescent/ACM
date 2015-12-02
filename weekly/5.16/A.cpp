#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAX = 410;
const int INF = 1e15;

vector<int> G[MAX];
int cap[MAX][MAX];
int cost[MAX][MAX];
int pi[MAX];
int dist[MAX];
int from[MAX];

int mcf(int src, int snk, int flow)
{
	for(int i = 0; i < MAX; i++)
		for(int j = 0; j < MAX; j++)
			if(cap[i][j])
				cost[j][i] = -cost[i][j];

	memset(pi, 0, sizeof(pi));

	int cst = 0;
	for(int f = 0; f < flow; )
	{
		for(int i = 0; i < MAX; i++) dist[i] = INF;
		memset(from, -1, sizeof(from));
		dist[src] = 0, from[src] = -2;
		priority_queue<pair<int, int> > q;
		q.push(make_pair(0, src));
		while(!q.empty())
		{
			pair<int, int> pr = q.top(); q.pop();
			int best = pr.second;
			if(abs(pr.first + dist[best]) > 0) continue;
			for(int vi = 0; vi < G[best].size(); vi++)
			{
				int i = G[best][vi];
				if(cap[best][i] && dist[best] + cost[best][i] + pi[best] - pi[i] < dist[i])
				{
					dist[i] = dist[best] + cost[best][i] + pi[best] - pi[i];
					from[i] = best;
					q.push(make_pair(-dist[i], i));
				}
			}
		}
		if(from[snk] == -1) return -1;
		for(int i = 0; i < MAX; i++) if(from[i] == -1) pi[i] += dist[i];

		int aug_f = flow - f;
		for(int v = snk; v != src; v = from[v])
			aug_f = min(aug_f, cap[from[v]][v]);

		for(int v = snk; v != src; v = from[v])
		{
			int u = from[v];
			cap[u][v] -= aug_f;
			cap[v][u] += aug_f;
			cst += aug_f * cost[u][v];
		}
		f += aug_f;
	}
	return cst;
}

void add_edge(int u, int v, int cp, int cst)
{
	cout << u << ' ' << v << ' ' << cp << ' ' << cst << endl;
	G[u].push_back(v);
	G[v].push_back(u);
    cap[u][v] = cp;
    cap[v][u] = 0;
    cost[u][v] = cst;
}

#define SRC 405
#define TEMP 406
#define SNK 407
#define IN(v) (2 + (v))
#define OUT(v) (203 + (v))

int N, M;
int H[MAX];
int trans[256][MAX];

int32_t main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> H[i];
	for(int i = 0; i <= N; i++)
	{
		add_edge(SRC, IN(i), 2000100, 0);
		add_edge(IN(i), OUT(i), 1e10, 0);
		add_edge(OUT(i), SNK, 2000100, 0);
	}
	int WEIGHT = 1e16;
	for(int i = 1; i < N; i++)
		add_edge(OUT(i), TEMP, 2000100 - (H[i + 1] - H[i]), -WEIGHT);
	add_edge(TEMP, SNK, 1e10, 0);
	while(M--)
	{
		char t;
		int l, c;
		cin >> t >> l >> c;
		if(trans[t][l]) trans[t][l] = min(trans[t][l], c);
		else trans[t][l] = c;
	}
	for(int l = 1; l <= N; l++)
	{
		if(trans['+'][l])
			for(int i = 1; i <= N; i++)
				add_edge(OUT(i), IN(i - l), 2000100, trans['+'][l]);
		if(trans['-'][l])
			for(int i = 1; i <= N; i++)
				add_edge(OUT(i - l), IN(i), 2000100, trans['-'][l]);
	}
	mcf(SRC, SNK, 1e10);
	for(int i = 1; i < N; i++)
	{
		if(cap[OUT(i)][TEMP])
		{
			cout << "-1\n";
			return 0;
		}
	}
	int ans = 0;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			if(i != j && cap[IN(j)][OUT(i)])
			{
				ans += cap[IN(j)][OUT(i)] * cost[OUT(i)][IN(j)];
				printf("%d -> %d: %d\n", i, j, cost[OUT(i)][IN(j)]);
			}
	cout << ans << endl;
	//cout << total_cost << endl;
	//cout << total_cost + (N - 1) * WEIGHT << endl;
}
