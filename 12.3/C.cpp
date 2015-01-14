#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int N;

vector<int> G[256][205];

bool reach[256][205][205];

bool vis[205];
void dfs(int t, int u)
{
	vis[u] = true;
	for(int i = 0; i < G[t][u].size(); i++)
	{
		int v = G[t][u][i];
		if(vis[v]) continue;
		dfs(t, v);
	}
}

int main()
{
	while(true)
	{
		for(int i = 0; i < 256; i++)
			for(int j = 0; j < 205; j++)
				G[i][j].clear();

		cin >> N;
		if(!N) break;
		while(true)
		{
			int u, v;
			cin >> u >> v;
			if(u == 0 && v == 0) break;
			string s;
			cin >> s;
			for(int i = 0; i < s.size(); i++)
				G[s[i]][u].push_back(v);
		}

		for(int c = 'a'; c <= 'z'; c++)
		{
			for(int s = 1; s <= N; s++)
			{
				memset(vis, 0, sizeof(vis));
				dfs(c, s);
				for(int i = 1; i <= N; i++)
					reach[c][s][i] = vis[i];
			}
		}

		while(true)
		{
			int u, v;
			cin >> u >> v;
			if(u == 0 && v == 0) break;
			string s;
			for(int c = 'a'; c <= 'z'; c++)
				if(reach[c][u][v]) s += c;
			if(s.empty()) s = "-";
			cout << s << '\n';
		}

		cout << '\n';
	}
}
