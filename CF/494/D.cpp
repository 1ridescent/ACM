#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;
#define MOD(x) (((x) + 1000000007000LL) % 1000000007)

int N;
vector<int> G[100005];
map<int, map<int, ll> > E;

ll shift1(ll sum0, ll sum1, ll t)
{
	return MOD(sum1 + MOD(t * sum0));
}
ll shift2(ll sum0, ll sum1, ll sum2, ll t)
{
	return MOD(sum2 + MOD(2 * t * sum1) + MOD(sum0 * MOD(t * t)));
}

ll S0[100005];
ll S1[100005];
ll S2[100005];
void calc_S(int u, int p)
{
	S0[u] = S1[u] = S2[u] = 0;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		calc_S(v, u);
		ll e = E[u][v];
		S0[u] = MOD(S0[u] + 1 + S0[v]);
		S1[u] = MOD(S1[u] + e + S1[v]);
		S2[u] = MOD(S2[u] + MOD(e * e) + S2[v]);
	}
}

ll sub1[100005];
ll sub2[100005];
void calc_sub(int u, int p)
{
	sub1[u] = sub2[u] = 0;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		calc_sub(v, u);
		sub1[u] = MOD(sub1[u] + shift1(S0[v] + 1, sub1[v], E[u][v]));
		sub2[u] = MOD(sub2[u] + shift2(S0[v] + 1, sub1[v], sub2[v], E[u][v]));
	}
}

ll super1[100005];
ll super2[100005];
void calc_super(int u, int p)
{
	super1[u] = super2[u] = 0;
	if(p != -1)
	{
		ll e = E[u][p];
		ll sub1p = MOD(sub1[p] - shift1(S0[u] + 1, S1[u], e));
		ll sub2p = MOD(sub2[p] - shift2(S0[u] + 1, S1[u], S2[u], e));
		ll sum0 = S0[1] - S0[u];
		ll sum1 = MOD(
	}
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		calc_super(v, u);
	}
}

ll sub1[100005];
ll super1[100005];
ll sub2[100005];
ll super2[100005];
void dfs(int u, int p)
{
	if(p == -1) // root
	{
		sub1[u] = S1[u];
		super1[u] = 0;
		sub2[u] = S2[u];
		super2[u] = 0;
	}
	else
	{
		sub1 = shift1(S0[p], )
	}
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		dfs(v, u);
	}
}

int V[100005];

int main()
{
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		G[a].push_back(b);
		G[b].push_back(a);
		E[a][b] = E[b][a] = c;
	}

	calc_S(1, -1);
}
