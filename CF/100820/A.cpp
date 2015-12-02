#include <bits/stdc++.h>

using namespace std;

const int MAX = 1005;

int cap[MAX][MAX];

int from[MAX];
queue<int> Q;
int augment_path(int s, int t)
{
	memset(from, -1, sizeof(from));

	from[s] = s;
	Q.push(s);
	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for(int v = 0; v < MAX; v++)
		{
			if(from[v] != -1) continue;
			if(cap[u][v] == 0) continue;
			from[v] = u;
			Q.push(v);
		}
	}
	if(from[t] == -1) return 0;

	int flow = cap[from[t]][t];
	for(int v = t; v != s; v = from[v])
	{
		int u = from[v];
		flow = min(flow, cap[u][v]);
	}

	for(int v = t; v != s; v = from[v])
	{
		int u = from[v];
		cap[u][v] -= flow;
		cap[v][u] += flow;
	}

	return flow;
}
int max_flow(int s, int t)
{
	int flow = 0;
	while(true)
	{
		int add = augment_path(s, t);
		if(add == 0) break;
		flow += add;
	}
	return flow;
}
void add_edge(int u, int v, int c = 1)
{
	cap[u][v] += c;
}

#define LEFT(i) i
#define RIGHT(i) (500 + (i))
#define SRC 1002
#define SNK 1003

int N, M;
int D0[505][505];
int D[505][505];
int P[505];

int S[505], F[505], T[505];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++)cin >> P[i];
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
		{
			cin >> D0[i][j];
			if(i != j) D0[i][j] += P[j];
			D[i][j] = D0[i][j];
		}
	for(int k = 1; k <= N; k++)
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

	for(int i = 0; i < M; i++)
		cin >> S[i] >> F[i] >> T[i];
	for(int i = 0; i < M; i++)
		for(int j = 0; j < M; j++)
		{
			if(T[i] + D0[S[i]][F[i]] + D[F[i]][S[j]] <= T[j])
			{
				//printf("Ti=%d D=%d Tj=%d\n", T[i], D0[F[i]][S[j]], T[j]);
				//printf("adding edge %d -> %d\n", i, j);
				add_edge(LEFT(i), RIGHT(j));
			}
		}
	for(int i = 0; i < M; i++)
	{
		add_edge(SRC, LEFT(i));
		add_edge(RIGHT(i), SNK);
	}
	cout << M - max_flow(SRC, SNK);
}
