#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

#define THR 5
const int MAX = (1 << 17);

ll bit[MAX];
void init()
{
	memset(bit, 0, sizeof(bit));
}
void insert(int i, ll v)
{
	i += 128;
	for(; i < MAX; i += i & -i) bit[i] += v;
}
ll lookup(int i)
{
	i += 128;
	ll res = 0;
	for(; i > 0; i -= i & -i) res += bit[i];
	return res;
}
ll seg(int l, int r)
{
	return lookup(r) - lookup(l - 1);
}

int N, M;
vector<int> G[MAX];
int start[MAX], end[MAX];
int dfs_time = 0;
vector<int> depth[MAX];
void dfs(int u, int p, int d)
{
	//printf("u=%d p=%d d=%d t=%d\n", u, p, d, dfs_time);
	depth[d].push_back(u);
	start[u] = dfs_time++;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		dfs(v, u, d + 1);
	}
	end[u] = dfs_time;
}

struct query
{
	int t, u, d, y;
};
query Q[MAX];
vector<pair<int, int> > extras[MAX]; // [depth] = (id, y)

ll ans[MAX];

ll add_depth[MAX];
vector<pair<int, int> > cur;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i < N; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, -1, 1);
	for(int i = 0; i < M; i++)
	{
		cin >> Q[i].t;
		if(Q[i].t == 1)
		{
			cin >> Q[i].d >> Q[i].y;
			Q[i].d++;
			cur.push_back(make_pair(Q[i].d, Q[i].y));
		}
		else
		{
			cin >> Q[i].u;
			ans[i] = seg(start[Q[i].u], end[Q[i].u] - 1);
			//printf("query %d: default = %d\n", i, (int)ans[i]);
			for(int j = 0; j < cur.size(); j++)
			{
				int d = cur[j].first;
				int y = cur[j].second;
				extras[d].push_back(make_pair(i, y));
			}
		}
		if((i + 1) % THR == 0)
		{
			memset(add_depth, 0, sizeof(add_depth));
			for(int j = 0; j < cur.size(); j++)
			{
				int d = cur[j].first;
				int y = cur[j].second;
				add_depth[d] += y;
			}
			for(int d = 1; d <= N; d++)
				if(add_depth[d])
				{
					for(int j = 0; j < depth[d].size(); j++)
					{
						int v = depth[d][j];
						//printf("%d is at depth %d - adding %d\n", v, d, add_depth[d]);
						insert(start[v], add_depth[d]);
					}
				}
			cur.clear();
		}
	}

	init();
	for(int d = 1; d <= N; d++)
	{
		if(extras[d].empty()) continue;
		for(int i = 0; i < depth[d].size(); i++)
		{
			int u = depth[d][i];
			//printf("depth %d insert %d at %d\n", d, u, start[u]);
			insert(start[u], 1);
		}
		for(int i = 0; i < extras[d].size(); i++)
		{
			int id = extras[d][i].first;
			int y = extras[d][i].second;
			int u = Q[id].u;
			ll cnt = seg(start[u], end[u] - 1);
			//printf("query %d: %d has %d children at depth %d, seg is %d %d\n", id, u, (int)cnt, d, start[u],end[u]);
			ans[id] += cnt * y;
		}
		for(int i = 0; i < depth[d].size(); i++)
		{
			int u = depth[d][i];
			insert(start[u], -1);
		}
	}
	for(int i = 0; i < M; i++)
		if(Q[i].t == 2)
			cout << ans[i] << '\n';
}
