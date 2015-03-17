#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> G[200005];

void shift(deque<int>& D)
{
	D.push_back(D.front());
	D.pop_front();
}

deque<int> found[2];
map<int, map<int, int> > freq;
deque<int> ans[3];
void output()
{
	bool found_two = false;
	for(int t = 0; t < 2; t++)
		for(int i = 0; i < found[t].size(); i++)
		{
			int j = (i + 1) % found[t].size();
			freq[found[t][i]][found[t][j]]++;
			if(freq[found[t][i]][found[t][j]] == 2) found_two = true;
		}
	if(!found_two){cout<<found[0].size()<<' '<<found[1].size()<<endl;exit(0);}//{for(int v:found[0])cout<<v<<' ';cout<<endl;for(int v:found[1])cout<<v<<' ';cout<<endl;exit(0);}
	int start, end;
	for(int i = 0; i < found[0].size(); i++)
	{
		int j = (i + 1) % found[0].size();
		int k = (i + 2) % found[0].size();
		if(freq[found[0][i]][found[0][j]] == 1 && freq[found[0][j]][found[0][k]] == 2)
			start = found[0][j];
		if(freq[found[0][i]][found[0][j]] == 2 && freq[found[0][j]][found[0][k]] == 1)
			end = found[0][j];
	}
	int i = 0;
	while(found[0][i] != start) i++;
	for(; found[0][i] != end; i++) ans[2].push_back(found[0][i]);
	ans[2].push_back(end);
	for(int t = 0; t < 2; t++)
	{
		i = 0;
		while(found[t][i] != end) i++;
		for(; found[t][i] != start; i = (i + 1) % found[t].size())
			ans[t].push_front(found[t][i]);
		ans[t].push_front(start);
	}
	printf("YES\n");
	for(int t = 0; t < 3; t++)
	{
		cout << ans[t].size();
		for(int v : ans[t]) printf(" %d", v);
		printf("\n");
	}
	exit(0);

}

int vis[200005];
int dfs_time = 1;
vector<int> cycle[200005];
vector<int> dfs_stack;
vector<int> mark;
map<int, int> idx;
void dfs(int u, int p)
{
	//cout << "at " << u << ", from " <<p<<endl;
	idx[u] = dfs_stack.size();
	dfs_stack.push_back(u);
	mark.push_back(0);
	vis[u] = dfs_time++;
	for(int v : G[u])
	{
		if(v == p) continue;
		if(vis[v] && vis[v] < vis[u])
		{
			int i = dfs_stack.size() - 1;
			int in_cycle = 0;
			while(true)
			{
				if(dfs_stack[i] == v) break;
				if(mark[i]) in_cycle = mark[i];
				i--;
			}
			if(in_cycle)
			{
				//printf("cycle: %d->%d,times%d %d\n",u,v,vis[u],vis[v]);
				for(int w : cycle[in_cycle]) found[0].push_back(w);
				for(; i < dfs_stack.size(); i++) found[1].push_back(dfs_stack[i]);
				output();
			}
			for(; i < dfs_stack.size(); i++)
			{
				cycle[v].push_back(dfs_stack[i]);
				if(dfs_stack[i] != v) mark[i] = v;
			}
		}
		else if(!vis[v]) dfs(v, u);
		cycle[u].clear();
	}
	dfs_stack.pop_back();
	mark.pop_back();
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i = 1; i <= N; i++)
		if(!vis[i])
			dfs(i, -1);
	printf("NO\n");
}
