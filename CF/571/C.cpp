#include <bits/stdc++.h>

using namespace std;

const int MAX = 500050;

int N, M;
vector<int> clauses[MAX];
bool good[MAX];

vector<pair<int, int> > var_occ[MAX]; // (clause, +/-x)
queue<int> queued; // if freq < 2
int result[MAX];

vector<pair<int, int> > G[MAX]; // (index,

int vis[MAX];


int find_root(int u, int x)
{
	vis[u] = 1;
	if(good[u]) return u;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first, y = G[u][i].second;
		if(abs(x) == abs(y)) continue;
		if(vis[v] == 1) return v;
		int r = find_root(v, y);
		if(r != -1) return r;
	}
	return -1;
}
void dfs(int u, int x, int r)
{
	vis[u] = 2;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first, y = G[u][i].second;
		if(abs(x) == abs(y)) continue;
		if(v == r)
		{
			result[abs(y)] = y;
			continue;
		}
		else if(vis[v] == 2) continue;
		//cout << u << ' ' << v << endl;
		result[abs(y)] = y;
		dfs(v, y, r);
	}
}
void assign(int u)
{
	int r = find_root(u, -222222222);
	//cout << "root of " << u << " is " << r << endl;
	if(r == -1)
	{
		cout << "NO\n";
		exit(0);
	}
	dfs(r, -111111111, r);
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
	{
		int k;
		cin >> k;
		while(k--)
		{
			int x;
			cin >> x;
			clauses[i].push_back(x);
			var_occ[abs(x)].push_back(make_pair(i, x));
		}
	}
	for(int x = 1; x <= M; x++)
	{
		if(var_occ[x].empty()) continue;
		else if(var_occ[x].size() == 1)
		{
			pair<int, int> a = var_occ[x][0];
			good[a.first] = true;
			result[x] = a.second;
		}
		else
		{
			pair<int, int> a = var_occ[x][0], b = var_occ[x][1];
			if(a.second == b.second)
			{
				good[a.first] = good[b.first] = true;
				result[x] = a.second;
			}
			else
			{
				G[a.first].push_back(b);
				G[b.first].push_back(a);
				//cout << "add " << a.first << ' ' << b.first << endl;
			}
		}
	}
	for(int i = 1; i <= N; i++)
	{
		//cout << "good " << i << " = " << good[i] << endl;
		if(!vis[i]) assign(i);
	}
	cout << "YES\n";
	for(int i = 1; i <= M; i++) cout << (result[i] > 0 ? 1 : 0);
}
