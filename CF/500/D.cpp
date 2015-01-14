#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstdio>

using namespace std;

typedef long long ll;

int N;
vector<int> G[100005];
int E[100005][3];
map<int, map<int, ll> > W;

ll size[100005];
void get_size(int u, int p)
{
	size[u] = 1;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		get_size(v, u);
		size[u] += size[v];
	}
}

ll C2(ll x)
{
	return x * (x - 1) / 2;
}
ll C3(ll x)
{
	return x * (x - 1) * (x - 2) / 6;
}

ll total = 0;
void query(int u, int v, ll w)
{
	ll delta = w - W[u][v];
	if(size[u] < size[v])
	{
		query(v, u, delta);
		return;
	}
	ll subsize = size[v];
	ll supersize = N - subsize;
	total += delta * (subsize * C2(supersize) + C2(subsize) * supersize);
	W[u][v] = w;
}

/*
ll one[100005];
void get_one(int u)
{
	one[u] = 0;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first, w = G[u][i].second;
		get_one(v);
		one[u] += (one[v] + size[v] * w);
	}
}

ll two[100005];
void get_two(int u)
{
	two[u] = 0;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first, w = G[u][i].second;

	}
}
*/
int main()
{
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		E[i][0] = u, E[i][1] = v, E[i][2] = w;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	get_size(1, -1);
	for(int i = 1; i < N; i++)
		query(E[i][0], E[i][1], E[i][2]);
	int Q;
	cin >> Q;
	while(Q--)
	{
		int e, w;
		cin >> e >> w;
		query(E[e][0], E[e][1], w);
		printf("%.9f\n", 2.0 * total / C3(N));
	}
}
