#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 205;

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
void init()
{
	memset(cap, 0, sizeof(cap));
}
void add_edge(int u, int v, int c)
{
	cap[u][v] += c;
}

int N, C;
int start[MAX], end[MAX], size[MAX];
int mat[MAX][MAX];

#define IN(u) (u)
#define OUT(u) ((u) + N)
#define INF 10000000

int main()
{
	ios::sync_with_stdio(false);

	int tests;
	cin >> tests;
	for(int test = 1; test <= tests; test++)
	{
		cin >> N >> C;

		init();
		for(int i = 1; i <= N; i++)
			cin >> start[i] >> end[i] >> size[i];
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
				cin >> mat[i][j];

		int source = 0, target = 2 * N + 1;
		int total = 0;
		for(int i = 1; i <= N; i++)
		{
			int c = (size[i] + C - 1) / C;
			total += c;
			add_edge(IN(i), source, c);
			add_edge(target, OUT(i), c);
		}
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
			{
				if(i == j) continue;
				if(end[i] + mat[i][j] < start[j])
					add_edge(OUT(i), IN(j), INF);
			}

		cout << "Case " << test << ": " << total - max_flow(target, source) << '\n';
	}
}
