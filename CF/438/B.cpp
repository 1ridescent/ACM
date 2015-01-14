#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef long long ll;

const int MAX = (1 << 17);

	int R[MAX];
	void init()
	{
		for(int i = 0; i < MAX; i++) R[i] = -1;
	}
	int find(int v)
	{
		if(R[v] < 0) return v;
		return find(R[v]);
	}
	void uni(int u, int v)
	{
		int ru = find(u), rv = find(v);
		if(-R[ru] <= -R[rv]) R[ru] = rv;
		else if(-R[ru] > -R[rv]) R[rv] = ru;
	}

int N, M;
int V[MAX];
struct edge
{
	int u, v, w;
};
vector<edge> E;
bool cmp(edge a, edge b)
{
	return a.w > b.w;
}
vector< pair<int, int> > MST[MAX]; // (v, w)

void mst()
{
	sort(E.begin(), E.end(), cmp);
	init();
	for(int i = 0; i < E.size(); i++)
	{
		edge e = E[i];
		int ru = find(e.u), rv = find(e.v);
		if(ru == rv) continue;
		MST[e.u].push_back( make_pair(e.v, e.w) );
		MST[e.v].push_back( make_pair(e.u, e.w) );
	}
}

int root;
vector<int> UFG[MAX];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> V[i];
	for(int i = 0; i < M; i++)
	{
		edge e;
		cin >> e.u >> e.v;
		e.w = min(V[e.u], V[e.v]);
		E.push_back(e);
	}
	mst();
	for(int i = 1; i <= N; i++)
	{
		if(R[i] < 0) root = i;
		else
		{
			UFG.push_back(make_pair())
		}
	}
}
