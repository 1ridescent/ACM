#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> G[100005];

void yes()
{
	cout << "Yes\n";
	exit(0);
}

bool path[100005];

void find_paths(int u, int p)
{
	bool good = true;
	for(int v : G[u])
	{
		if(v == p) continue;
		find_paths(v, u);
		if(!path[v]) good = false;
	}
	if(G[u].size() > 2) good = false;
	path[u] = good;
}

bool is_end[100005];

bool Try(int u, int p)
{
	int bad1 = -1, bad2 = -1;
	for(int v : G[u])
	{
		if(v == p) continue;
		if(path[v] || is_end[v]) continue;
		if(bad1 == -1) bad1 = v;
		else if(bad2 == -1)
		{
			if(p != -1) return false;
			bad2 = v;
		}
		else return false;
	}
	bool res = true;
	if(bad1 != -1) res &= Try(bad1, u);
	if(bad2 != -1) res &= Try(bad2, u);
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	bool all_deg2 = true;
	int root;
	for(int i = 1; i <= N; i++)
		if(G[i].size() > 2)
		{
			all_deg2 = false;
			root = i;
			break;
		}
	if(all_deg2) yes();
	find_paths(root, -1);
	for(int u = 1; u <= N; u++)
	{
		if(G[u].size() == 3)
		{
			int num_bad = 0;
			for(int v : G[u])
				if(!path[v]) num_bad++;
			if(num_bad <= 1) is_end[u] = true;
		}
	}
	if(Try(root, -1)) yes();
	for(int v : G[root])
		if(!path[v])
			if(Try(v, -1)) yes();
	cout << "No\n";
}
