#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

typedef long double ld;
const ld inf = 1e9;
const ld eps = 1e-12;

int N, M, E;
vector<int> G[105];
ld D[105][105];
ld police[105];
ld edge[105][105];
int S, P;

bool is_exit[105];
ld dist[105];
priority_queue< pair<ld, int> > Q;

bool test(ld speed)
{
	while(!Q.empty()) Q.pop();
	for(int i = 0; i < 105; i++) dist[i] = -1;

	Q.push( make_pair(-0.0, S) );
	while(!Q.empty())
	{
		int u = Q.top().second;
		ld t = -Q.top().first;
		Q.pop();

		if(dist[u] >= 0) continue;
		if(is_exit[u]) return true;

		//cout << u << ' ' << t << endl;
		dist[u] = t;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if(dist[v] >= 0) continue;
			ld t2 = t + (edge[u][v] / speed);
			if(police[v] <= t2) continue;

			Q.push( make_pair(-t2, v) );
		}
	}
	return false;
}

int main()
{
	for(int i = 0; i < 105; i++)
		for(int j = 0; j < 105; j++)
		{
			if(i == j) D[i][j] = 0;
			else edge[i][j] = D[i][j] = inf - 10;
		}

	cin >> N >> M >> E;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		ld c;
		cin >> a >> b >> c;
		c *= 0.1;
		G[a].push_back(b);
		G[b].push_back(a);
		D[a][b] = min(D[a][b], c);
		D[b][a] = min(D[b][a], c);
		edge[a][b] = min(edge[a][b], c);
		edge[b][a] = min(edge[b][a], c);
	}
	for(int k = 1; k <= N; k++)
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

	memset(is_exit, 0, sizeof(is_exit));
	for(int i = 0; i < E; i++)
	{
		int a;
		cin >> a;
		is_exit[a] = true;
	}

	cin >> S >> P;
	for(int i = 1; i <= N; i++)
	{
		police[i] = D[P][i] / 160.0;
		//cout << i << ' ' << police[i] << endl;
	}

	ld low = 0, high = inf;
	while(high - low > eps)
	{
		ld mid = (low + high) / 2.0;
		if(test(mid)) high = mid;
		else low = mid;
	}
	if(high == inf) cout << "IMPOSSIBLE\n";
	else printf("%.9f\n", (double)high);
}
