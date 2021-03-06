#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define inv2 500000004

map<int, vector<pair<int, int> > > G;
map<int, int> color;
bool bad = false;
void dfs(int u, int c)
{
	color[u] = c;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first, w = G[u][i].second;
		if(!color.count(v)) dfs(v, c ^ w);
		else if((c ^ w) != color[v]) bad = true;
	}
}
ll two_color()
{
	ll r = 1;
	for(map<int, vector<pair<int, int> > >::iterator it = G.begin(); it != G.end(); it++)
	{
		int u = it->first;
		if(color.count(u)) continue;
		//cout << "dfs at " << u << endl;
		dfs(u, 0);
		r = (r * 2) % mod;
	}
	if(bad) return 0;
	return r;
}
#define T 10000000
void insert2(int u, int v, int c)
{
	//printf("%d %d %d\n", u, v, c);
	G[u].push_back(make_pair(v, c));
	G[v].push_back(make_pair(u, c));
}
void insert(int n, int m, int c)
{
	if((n + m) % 2)
		insert2(n + m, T + n - m, c);
	else
		insert2(2 * T + n + m, 3 * T + n - m, c);
}

int N, K;

int main()
{
	cin >> N >> K;
	for(int i = 0; i <= N + 1; i++)
	{
		insert(0, i, 0);
		insert(i, 0, 0);
		insert(N + 1, i, 0);
		insert(i, N + 1, 0);
	}
	while(K--)
	{
		int r, c;
		cin >> r >> c;
		char k;
		cin >> k;
		insert(r, c, k == 'o');
	}
	cout << (((two_color() * inv2) % mod) * inv2) % mod << endl;
}
