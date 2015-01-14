#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iomanip>

using namespace std;

typedef pair<int, int> point;
#define x first
#define y second

const double inf = 1e9;

double dist(point a, point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int N, M;
point P[505];

#define index(v1, v2) ((v1) * N + (v2))

struct edge
{
	int u, v;
	double w;
};
bool cmp(edge a, edge b)
{
	return a.w > b.w;
}
vector<edge> G[250025];

vector<edge> E;
void add_edge(int u1, int u2, int v1, int v2)
{
	edge e;
	e.w = min(dist(P[u1], P[u2]), dist(P[v1], P[v2]));
	e.u = index(u1, u2), e.v = index(v1, v2);
	E.push_back(e);
	G[index(u1, u2)].push_back(e);
	e.u = index(v1, v2), e.v = index(u1, u2);
	E.push_back(e);
	G[index(v1, v2)].push_back(e);
}

int R[250025];
double W[250025];
void init()
{
	for(int i = 0; i < N * N; i++)
	{
		R[i] = -1;
		W[i] = inf;
	}
}
int find(int u)
{
	if(R[u] < 0) return u;
	return find(R[u]);
}
void uni(int u, int v, double w)
{
	u = find(u), v = find(v);
	//cout << "R " << u / N << ',' << u% N << ' ' << v/N << ',' << v%N << ' ' << w << endl;
	if(-R[u] > -R[v])
	{
		R[v] = u;
		W[v] = w;
	}
	else if(-R[u] < -R[v])
	{
		R[u] = v;
		W[u] = w;
	}
	else
	{
		R[u] = v;
		W[u] = w;
		R[v]--;
	}
}

void mst()
{
	sort(E.begin(), E.end(), cmp);
	init();
	for(int i = 0; i < E.size(); i++)
	{
		edge e = E[i];
		if(find(e.u) == find(e.v)) continue;
		uni(e.u, e.v, e.w);
	}
}

bool vis[250025];
double path(int s, int t)
{
	int v = s;
	do
	{
		vis[v] = true;
		v = R[v];
	}
	while(v >= 0);

	int lca = t;
	while(!vis[lca]) lca = R[lca];

	double res = inf;
	v = s;
	while(v != lca)
	{
		//cout << "R " << v << ' ' << W[v] << endl;
		res = min(res, W[v]);
		v = R[v];
	}
	v = t;
	while(v != lca)
	{
		//cout << "R " << v << ' ' << W[v] << endl;
		res = min(res, W[v]);
		v = R[v];
	}

	v = s;
	do
	{
		vis[v] = false;
		v = R[v];
	}
	while(v >= 0);

	return res;
}

void queries()
{
	memset(vis, 0, sizeof(vis));

	int Q;
	cin >> Q;
	while(Q--)
	{
		int a, b;
		cin >> a >> b;
		a--, b--;
		cout << path(index(a, b), index(b, a)) << endl;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cout << setprecision(9) << fixed;
	cin >> N;
	for(int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;
	cin >> M;
	for(int m = 0; m < M; m++)
	{
		int a, b;
		cin >> a >> b;
		a--, b--;
		double w = dist(P[a], P[b]);
		for(int i = 0; i < N; i++)
		{
			if(i == a || i == b) continue;
			add_edge(i, a, i, b);
			add_edge(a, i, b, i);
		}
	}
	//cout << "constructed graph" << endl;
	mst();
	//cout << "ran mst" << endl;
	queries();
}
