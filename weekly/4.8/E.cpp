#include <bits/stdc++.h>

using namespace std;

const int MAX = 252525;

vector<int> uf[MAX];
int rep[MAX];
int size[MAX];
int ans[MAX];
void mark(int u, int s)
{
	if(ans[u]) return;
	//printf("mark %d %d\n", u, s);
	ans[u] = s;
	for(int i = 0; i < uf[u].size(); i++)
		mark(uf[u][i], s);
}
int init()
{
	for(int i = 0; i < MAX; i++)
		rep[i] = -1, size[i] = 1;
}
int find(int u)
{
	if(rep[u] < 0) return u;
	return find(rep[u]);
}
void uni(int u, int v)
{
	u = find(u);
	v = find(v);
	if(-rep[u] < -rep[v])
	{
		uf[v].push_back(u);
		rep[u] = v;
		size[v] += size[u];
	}
	else if(-rep[u] > -rep[v])
	{
		uf[u].push_back(v);
		rep[v] = u;
		size[u] += size[v];
	}
	else
	{
		uf[v].push_back(u);
		rep[u] = v;
		rep[v]--;
		size[v] += size[u];
	}
}

#define INDEX(r, c) ((r) * 500 + (c))

int N, M, T;

int elev[505][505];
vector<int> starts;
vector<pair<int, pair<int, int> > > edges;
void add_edge(int u, int v, int c)
{
	edges.push_back(make_pair(c, make_pair(u, v)));
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M >> T;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			cin >> elev[i][j];
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			int c;
			cin >> c;
			if(c) starts.push_back(INDEX(i, j));
		}
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			if(i < N) add_edge(INDEX(i, j), INDEX(i + 1, j), abs(elev[i][j] - elev[i + 1][j]));
			if(j < M) add_edge(INDEX(i, j), INDEX(i, j + 1), abs(elev[i][j] - elev[i][j + 1]));
		}
	sort(edges.begin(), edges.end());
	init();
	for(int i = 0; i < edges.size(); i++)
	{
		int d = edges[i].first, u = edges[i].second.first, v = edges[i].second.second;
		if(find(u) != find(v))
		{
			//printf("%d %d\n", u, v);
			int fu = find(u), fv = find(v);
			uni(u, v);
			if(size[find(u)] >= T)
			{
				mark(find(u), d);
				mark(fu, d);
				mark(fv, d);
			}
		}
	}
	long long res = 0;
	for(int i = 0; i < starts.size(); i++)
		res += ans[starts[i]];
	cout << res << endl;
}
