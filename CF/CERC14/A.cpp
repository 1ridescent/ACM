#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

const int MAX = 1024;

int N;
vector<int> G0[MAX];
vector<int> G[MAX];
int size[MAX];
int par[MAX];
int depth[MAX];
vector<int> child[MAX];
bool is_child[MAX][MAX];
int lca[MAX][MAX];

void build_tree(int u, int p, int d)
{
	par[u] = p;
	depth[u] = d;
	for(int i = 0; i < G0[u].size(); i++)
	{
		int v = G0[u][i];
		if(v == p) continue;
		build_tree(v, u, d + 1);
		G[u].push_back(v);
		child[u].push_back(v);
		is_child[v][u] = true;
		for(int j = 0; j < child[v].size(); j++)
		{
			child[u].push_back(child[v][j]);
			is_child[child[v][j]][u] = true;
		}
	}

	size[u] = G[u].size();
}

int get_lca(int a, int b)
{
	//cout << " at " << a << ' ' << b << endl;
	if(lca[a][b] != 0) return lca[a][b];

	if(a == b) lca[a][b] = a;
	else if(par[a] == -1) lca[a][b] = a;
	else if(par[b] == -1) lca[a][b] = b;
	else
	{
		int l1 = get_lca(par[a], b);
		int l2 = get_lca(a, par[b]);
		if(l1 == l2) lca[a][b] = l1;
		else if(l1 == par[l2]) lca[a][b] = l2;
		else if(l2 == par[l1]) lca[a][b] = l1;
		else assert(false);
	}
	return lca[a][b];
}

vector< pair<int, int> > root[MAX];
int jump[MAX][10];
int val[MAX][10];

int get_path(int s, int d)
{
	int v = 0;
	//printf("get_path(%d, %d) = ", s, d);
	for(int i = 0; i < 10; i++)
	{
		if(d & (1 << i))
		{
			v += val[s][i];
			s = jump[s][i];
		}
	}
	//printf("%d\n", v);
	return v;
}

int dp[MAX];
int sub[MAX];
int temp[10][10];
void compute(int u)
{
	for(int i = 0; i < size[u]; i++)
		compute(G[u][i]);

	for(int i = 0; i < (1 << size[u]); i++)
		dp[i] = 0;

	memset(temp, 0, sizeof(temp));
	for(int i = 0; i < size[u]; i++)
		temp[i][i] = sub[G[u][i]];
	for(int i = 0; i < root[u].size(); i++)
	{
		int a = root[u][i].first, b = root[u][i].second;
		//printf("%d: path %d -- %d\n", u, a, b);
		if(a == u) swap(a, b);

		int d = depth[a] - depth[u];
		int v = sub[a] + get_path(a, d - 1);
		int i1 = -1;
		for(int j = 0; j < G[u].size(); j++)
		{
			int c = G[u][j];
			if(c == a || is_child[a][c])
				i1 = j;
		}
		int i2 = i1;
		if(b != u)
		{
			d = depth[b] - depth[u];
			int v2 = sub[b] + get_path(b, d - 1);
			v += v2;
			for(int j = 0; j < G[u].size(); j++)
			{
				int c = G[u][j];
				if(c == b || is_child[b][c])
					i2 = j;
			}
		}
		v++;
		//printf("%d: temp[%d][%d] = %d\n", u, i1, i2, v);
		temp[i1][i2] = max(temp[i1][i2], v);
	}

	for(int b = 0; b < (1 << size[u]); b++)
	{
		for(int i = 0; i < size[u]; i++)
			if(!(b & (1 << i)))
			{
				for(int j = 0; j < size[u]; j++)
				{
					if(!(b & (1 << j)))
					{
						dp[b | (1 << i) | (1 << j)] = max(dp[b | (1 << i) | (1 << j)], dp[b] + temp[i][j]);
					}
				}
			}
	}

	sub[u] = dp[(1 << size[u]) - 1];
	//printf("sub[%d] = %d\n", u, sub[u]);

	for(int i = 0; i < G[u].size(); i++)
	{
		int c = G[u][i];
		jump[c][0] = u;
		val[c][0] = dp[((1 << size[u]) - 1) ^ (1 << i)];
		//printf("jump[%d][%d] = %d\n", c, 0, jump[c][0]);
		//printf("val[%d][%d] = %d\n", c, 0, val[c][0]);
	}
	for(int i = 1; i < 10; i++)
	{
		for(int i2 = 0; i2 < child[u].size(); i2++)
		{
			int c = child[u][i2];
			int d = depth[c] - depth[u];
			if((1 << i) == d)
			{
				jump[c][i] = u;
				val[c][i] = val[c][i - 1] + val[jump[c][i - 1]][i - 1];
				//printf("jump[%d][%d] = %d\n", c, i, jump[c][i]);
				//printf("val[%d][%d] = %d\n", c, i, val[c][i]);
			}
		}
	}
}

int main2()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		G0[i].clear();
		G[i].clear();
		child[i].clear();
		root[i].clear();
		for(int j = 1; j <= N; j++)
		{
			is_child[i][j] = false;
			lca[i][j] = 0;
		}
	}

	for(int i = 1; i < N; i++)
	{
		int a, b;
		cin >> a >> b;
		G0[a].push_back(b);
		G0[b].push_back(a);
	}
	build_tree(1, -1, 0);

	int M;
	cin >> M;
	while(M--)
	{
		int a, b;
		cin >> a >> b;
		root[get_lca(a, b)].push_back(make_pair(a, b));
		//printf("lca[%d][%d] = %d\n", a, b, lca[a][b]);
	}

	compute(1);
	cout << sub[1] << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) main2();
}
