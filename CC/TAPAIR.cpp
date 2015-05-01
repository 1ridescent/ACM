#include <bits/stdc++.h>

using namespace std;

const int MAX = 100005;

int N, M;
set<int> G0[MAX];

int rep[MAX];
int find(int u)
{
	if(rep[u] == u) return u;
	rep[u] = find(rep[u]);
	return rep[u];
}
void uni(int u, int v)
{
	R[find(u)] = find(v);
}


int timestamp = 0;
int vis_time[MAX];
int id[MAX];
map<pair<int, int>, int> dfs_stack;

void mark(int u)
{
	if(vis_time[u] != -1) return;
	vis_time[u] = timestamp++;
	id[vis_time[u]] = u;
}

void dfs(int u)
{
	while(!G[u].empty())
	{
		int v = *(G[u].begin());
		if(vis_time[v] != -1)
		{
			map<int, int>::iterator it = dfs_stack.lower_bound(make_pair(vis_time[v], -1));
			map<int, int>::iterator it2;
			while(it != dfs_stack.end())
			{
				it2 = it;
				it++;
				it2->second++;
				if(it2->second == 2)
				{
					uni(id[it2->first.first], id[it2->first.second]);
					dfs_stack.erase(it2);
				}
			}
		}
		else mark(v);
		dfs_stack[make_pair(vis_time[u], vis_time[v])] = 0;
		dfs(v);
		dfs_stack.erase(make_pair(vis_time[u], vis_time[v]));
	}
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int u, v;
		cin >> u >> v;
		G0[u].insert(v);
		G0[v].insert(u);
	}
	for(int i = 1; i <= N; i++) rep[i] = i;
	mark(1);
	dfs(1);
}
