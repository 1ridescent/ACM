/***** MAX-FLOW *****/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
#include <set>

using namespace std;

const int MAX = 107;

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

const int S = 104, T = 105;

int N, M;

int A[105];
set<int> factors;
map<int, int> factor[105];
int E[105][2];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
	{
		int x;
		cin >> x;
		A[i] = x;
		for(int f = 2; f < 40000; f++)
		{
			while(x % f == 0)
			{
				factor[i][f]++;
				x /= f;
				factors.insert(f);
			}
		}
		if(x > 1)
		{
			int f = x;
			factor[i][f]++;
			factors.insert(f);
		}
	}
	for(int i = 0; i < M; i++)
	{
		int x, y;
		cin >> x >> y;
		if(x % 2 == 1)
			E[i][0] = x, E[i][1] = y;
		else
			E[i][0] = y, E[i][1] = x;
	}
	int ans = 0;
	for(set<int>::iterator it = factors.begin(); it != factors.end(); it++)
	{
		int f = *it;
		init();
		for(int i = 1; i <= N; i++)
		{
			if(i % 2 == 1)
				add_edge(S, i, factor[i][f]);
			else
				add_edge(i, T, factor[i][f]);
		}
		for(int i = 0; i < M; i++)
			add_edge(E[i][0], E[i][1], 10000000);
		ans += max_flow(S, T);
	}
	cout << ans;
}
