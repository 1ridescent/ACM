#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct edge
{
	int u, v, w;
};
vector<edge> E;
bool cmp(edge a, edge b)
{
	return a.w < b.w;
}

int R[252525];
vector<int> Rtree[252525];
int size[252525];
int val[252525];
int init_R()
{
	for(int i = 0; i < 252525; i++) size[i] = 1, R[i] = -1;
}
int Find(int v)
{
	if(R[v] < 0) return v;
	return Find(R[v]);
}
int Union(int u, int v)
{
	int Ru = Find(u), Rv = Find(v);
	if(-Ru > -Rv)
	{
		Rtree[Ru].push_back(Rv);
		size[Ru] += size[Rv];
		R[Rv] = Ru;
		R[Ru]--;
	}
	else
	{
		Rtree[Rv].push_back(Ru);
		size[Rv] += size[Ru];
		R[Ru] = Rv;
		R[Rv]--;
	}
}
void mark(int v, int m)
{
	//cout << v << "->" << m << endl;
	val[v] = m;
	for(int i = 0; i < Rtree[v].size(); i++)
		mark(Rtree[v][i], m);
}

#define index(r, c) ((r) * M + (c))

int N, M, T;
int G[505][505];

int main()
{
	freopen("skilevel.in", "r", stdin), freopen("skilevel.out", "w", stdout);
	init_R();
	cin >> N >> M >> T;
	for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) cin >> G[i][j];
	for(int i = 0; i < N-1; i++)
		for(int j = 0; j < M; j++)
		{
			edge e;
			e.u = index(i,j), e.v = index(i+1,j), e.w = abs(G[i][j] - G[i+1][j]);
			E.push_back(e);
		}
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M-1; j++)
		{
			edge e;
			e.u = index(i,j), e.v = index(i,j+1), e.w = abs(G[i][j] - G[i][j+1]);
			E.push_back(e);
		}
	sort(E.begin(), E.end(), cmp);
	for(int i = 0; i < E.size(); i++)
	{
		int u = E[i].u, v = E[i].v;
		int Ru = Find(u), Rv = Find(v);
		if(Ru == Rv) continue;
		int sizeu = size[Ru], sizev = size[Rv];
		//printf("u=%d v=%d w=%d su=%d sv=%d  ",u,v,E[i].w,sizeu,sizev);
		if(sizeu + sizev >= T)
		{
			if(sizeu < T) mark(Ru, E[i].w);
			if(sizev < T) mark(Rv, E[i].w);
		}
		Union(Ru, Rv);
		//cout << "newsize=" << -R[Find(u)] << endl;
	}
	long long total = 0;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < M; j++)
		{
			int b;
			cin >> b;
			if(b) total += val[index(i, j)];
		}
	}
	//for(int i = 0; i < 15; i++) cout << size[i] << ' '; cout << endl;
	cout << total << endl;
	return 0;
}
