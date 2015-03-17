#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<pair<int, int> > G[100005];

void dfs_find(int u, int p, vector<int>& V)
{
	V.push_back(u);
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first, c = G[u][i].second;
		if(v == p) continue;
		dfs_find(v, u, V);
	}
}
int score[100005];
void dfs_score(int u, int p, int m)
{
	score[u] = m;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first, c = G[u][i].second;
		if(v == p) continue;
		dfs_score(v, u, m + c);
	}
}
int marks[200010];
bool is_marked[100005];
void dfs_mark(int u, int p)
{
	is_marked[u] = marks[100005 + score[u]];
	marks[100005 + score[u]]++;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first, c = G[u][i].second;
		if(v == p) continue;
		dfs_mark(v, u);
	}
	marks[100005 + score[u]]--;
}

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


ll div_conquer(int u0)
{
	int r = balance(u0);
	ll ans = 0;
	map<int, int> cnt[2];
	for(int i = 0; i < G[r].size(); i++)
	{
		map<int, int> temp[2];
		int u = G[r][i].first, c = G[r][i].second;
		vector<int> V;
		dfs_find(u, r, V);
		dfs_score(u, r, c);
		dfs_mark(u, r);
		for(int i = 0; i < V.size(); i++)
		{
			int v = V[i];
			if(score[v] == 0)
			{
				ans += is_marked[v];
				ans += cnt[0][0] + cnt[1][0];
			}
			else
			{
				ans += cnt[1][-score[v]];
				if(is_marked[v]) ans += cnt[0][-score[v]];
			}
			temp[is_marked[v]][score[v]]++;
		}
		for(int t = 0; t < 2; t++)
			for(map<int, int>::iterator it = temp[t].begin(); it != temp[t].end(); it++)
				cnt[t][it->first] += it->second;
	}
	for(int i = 0; i < G[r].size(); i++)
	{
		int v = G[r][i].first;
		for(int j = 0; j < G[v].size(); j++)
			if(G[v][j].first == r)
			{
				G[v].erase(G[v].begin() + j);
				break;
			}
		ans += div_conquer(v);
	}
	return ans;
}

int main()
{
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int u, v, c;
		cin >> u >> v >> c;
		if(c == 0) c = -1;
		G[u].push_back(make_pair(v, c));
		G[v].push_back(make_pair(u, c));
	}
	cout << div_conquer(1) << endl;
}
