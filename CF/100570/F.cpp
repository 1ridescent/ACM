#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;

int N, M;

vector<pair<int, ll> > G[100005];
vector<pair<ll, int> > Q[100005];
int ans[100005];

int size[100005];
ll depth[100005];
vector<int> vis;
void get_info(int u, int p, ll d)
{
	vis.push_back(u);
	size[u] = 1 + Q[u].size();
	depth[u] = d;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		ll w = G[u][i].second;
		if(v == p) continue;
		get_info(v, u, d + w);
		size[u] += size[v];
	}
	//printf("size[%d] = %d\n", u, size[u]);
}

int balance(int u)
{
	vis.clear();
	get_info(u, -1, 0);
	int n = size[u];
	for(int ri = 0; ri < vis.size(); ri++)
	{
		int r = vis[ri];
		bool is_root = true;
		for(int i = 0; i < G[r].size(); i++)
		{
			int v = G[r][i].first;
			if(size[v] > size[r]) continue;
			//printf("%d -> %d: size = %d, n = %d\n", r, v, size[v], n);
			if(2 * size[v] > n)
				is_root = false;
		}
		//printf("%d up: size = %d, n = %d\n", r, n - size[r], n);
		if(2 * (n - size[r]) > n)
			is_root = false;
		if(is_root)
		{
			vis.clear();
			get_info(r, -1, 0);
			//printf("root = %d\n", r);
			return r;
		}
	}
	assert(false);
}

void remove_edge(int u, int v)
{
	for(int i = 0; i < G[u].size(); i++)
		if(G[u][i].first == v)
		{
			G[u].erase(G[u].begin() + i);
			break;
		}
}

void process(vector<ll>& depths, vector<pair<ll, int> >& queries, int s)
{
	int di = 0, qi = 0;
	for(int i = 0; i < queries.size(); i++)
	{
		ll q = queries[i].first;
		while(di < depths.size() && depths[di] <= q)
			di++;
		ans[queries[i].second] += s * di;
	}
}

void compute(int r)
{
	r = balance(r);
	//printf("computing %d\n", r);
	vector<ll> all_d;
	vector<pair<ll, int> > all_q;
	all_d.push_back(0);
	for(int i = 0; i < Q[r].size(); i++)
		all_q.push_back(Q[r][i]);
	for(int ui = 0; ui < G[r].size(); ui++)
	{
		int u = G[r][ui].first;
		ll w = G[r][ui].second;
		vis.clear();
		get_info(u, r, w);
		vector<ll> single_d;
		vector<pair<ll, int> > single_q;
		for(int vi = 0; vi < vis.size(); vi++)
		{
			int v = vis[vi];
			all_d.push_back(depth[v]);
			single_d.push_back(depth[v]);
			for(int i = 0; i < Q[v].size(); i++)
			{
				all_q.push_back(make_pair(Q[v][i].first - depth[v], Q[v][i].second));
				single_q.push_back(make_pair(Q[v][i].first - depth[v], Q[v][i].second));
			}
		}
		sort(single_d.begin(), single_d.end());
		sort(single_q.begin(), single_q.end());
		process(single_d, single_q, -1);
	}
	sort(all_d.begin(), all_d.end());
	sort(all_q.begin(), all_q.end());
	process(all_d, all_q, 1);
	for(int ui = 0; ui < G[r].size(); ui++)
	{
		int u = G[r][ui].first;
		ll w = G[r][ui].second;
		remove_edge(u, r);
		compute(u);
	}
}

int main()
{
	cin >> N >> M;
	for(int i = 1; i < N; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		G[a].push_back(make_pair(b, c));
		G[b].push_back(make_pair(a, c));
	}
	for(int i = 0; i < M; i++)
	{
		int u;
		ll d;
		cin >> u >> d;
		Q[u].push_back(make_pair(d, i));
	}
	memset(ans, 0, sizeof(ans));
	compute(1);
	for(int i = 0; i < M; i++)
		cout << ans[i] << '\n';
}
