#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

int N;
vector<pair<int, ll> > G[100005];

ll down[100005], up[100005];
ll dist[100005];
void dfs_down(int u, int p)
{
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		ll w = G[u][i].second;
		if(v == p) continue;
		dfs_down(v, u);
		down[u] = max(down[u], w + down[v]);
	}
}
void dfs_up(int u, int p)
{
	vector<pair<ll, int> > V;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		ll w = G[u][i].second;
		if(v == p) continue;
		V.push_back(make_pair(w + down[v], v));
	}
	sort(V.begin(), V.end());
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		ll w = G[u][i].second;
		if(v == p) continue;
		if(v != V.back().second) up[v] = w + max(up[u], V.back().first);
		else if(V.size() >= 2) up[v] = w + max(up[u], V[V.size() - 2].first);
		else up[v] = w + up[u];
	}
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		ll w = G[u][i].second;
		if(v == p) continue;
		dfs_up(v, u);
	}
}
void compute_dist()
{
	dfs_down(1, -1);
	dfs_up(1, -1);
	for(int i = 1; i <= N; i++) dist[i] = max(up[i], down[i]);
}


vector<ll> queries;
int ans[100005];

int size[100005];
void dfs_size(int u, int p)
{
	size[u] = 1;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		if(v == p) continue;
		dfs_size(v, u);
		size[u] += size[v];
	}
}
int balance_root;
void dfs_balance(int u, int p, int s)
{
	bool good = (2 * (s - size[u]) <= s);
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		if(v == p) continue;
		if(2 * size[v] > s) good = false;
		dfs_balance(v, u, s);
	}
	if(good) balance_root = u;
}
int balance(int u)
{
	dfs_size(u, -1);
	balance_root = -1;
	dfs_balance(u, -1, size[u]);
	assert(balance_root != -1);
	return balance_root;
}

int score;
bool in[100005];
int P[100005];
bool valid[100005];
void invalidate(int u)
{
	if(!valid[u]) return;
	valid[u] = false;
	if(in[u]) score--;
	in[u] = false;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		if(v == P[u]) continue;
		invalidate(v);
	}
}

priority_queue<pair<ll, int> > Q;
vector<int> dfs_order;
vector<pair<ll, int> > dist_order;

void div_conquer(int u0)
{
	int r = balance(u0);
	Q.push(make_pair(-dist[r], r));
	P[r] = -1;
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		dfs_order.push_back(u);
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].first;
			if(v == P[u]) continue;
			Q.push(make_pair(-dist[v], v));
			P[v] = u;
		}
	}
	//cout << "dfs_order at " << r << ": "; for(int i = 0; i < dfs_order.size(); i++) cout << dfs_order[i] << ' '; cout << endl;
	for(int i = 0; i < dfs_order.size(); i++)
	{
		int u = dfs_order[i];
		dist_order.push_back(make_pair(dist[u], u));
	}
	sort(dist_order.begin(), dist_order.end());
	//cout << "dist_order at " << r << ": "; for(int i = 0; i < dist_order.size(); i++) cout << dist_order[i].second << ":" << dist_order[i].first << ' '; cout << endl;

	for(int q = 0; q < queries.size(); q++)
	{
		for(int i = 0; i < dfs_order.size(); i++)
		{
			int u = dfs_order[i];
			in[u] = false;
			valid[u] = true;
		}
		score = 0;

		ll d = queries[q];
		ll maxdist = 0;
		int p = 0;
		for(int i = 0; i < dfs_order.size(); i++)
		{
			int u = dfs_order[i];
			//cout << "at " << u << ", dist = " << dist[u] << "\n";
			maxdist = max(maxdist, dist[u]);
			if(valid[u])
			{
				in[u] = true;
				score++;
			}
			while(p < dist_order.size() && maxdist - dist_order[p].first > d)
			{
				//cout << "invalidating " << dist_order[p].second << endl;
				invalidate(dist_order[p].second);
				p++;
			}
			//cout << u << " : " << "maxdist = " << maxdist << ", p = " << p << ", score = " << score << endl;
			ans[q] = max(ans[q], score);
		}
	}

	dfs_order.clear();
	dist_order.clear();

	for(int i = 0; i < G[r].size(); i++)
	{
		int v = G[r][i].first;
		for(int j = 0; j < G[v].size(); j++)
			if(G[v][j].first == r)
			{
				G[v].erase(G[v].begin() + j);
				break;
			}
		div_conquer(v);
	}
}


int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int u, v, c;
		cin >> u >> v >> c;
		G[u].push_back(make_pair(v, c));
		G[v].push_back(make_pair(u, c));
	}
	compute_dist();
	//for(int i = 1; i <= N; i++) cout << dist[i] << ' '; cout << endl;
	//cout << balance(1) << endl; return 0;
	int q;
	cin >> q;
	while(q--)
	{
		ll d;
		cin >> d;
		queries.push_back(d);
	}
	div_conquer(1);
	for(int i = 0; i < queries.size(); i++)
		cout << ans[i] << '\n';
}
