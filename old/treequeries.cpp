#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

const int MAX = (1 << 18);

int N, M;
int color[100100];
vector<int> G[MAX];
vector<int> GC[MAX]; // color graph
vector<int> current[MAX]; // [i] : color of current
void dfs(int v, int p)
{
	int c = color[v]; // current color
	if(!current[c].empty())
	{
		int u = current[c].back();
		GC[u].push_back(v);
		cout << u << "-->" << v << endl;
	}
	current[c].push_back(v);
	for(int i = 0; i < G[v].size(); i++)
	{
		int w = G[v][i];
		if(w == p) continue;
		dfs(w, v);
	}
	current[c].pop_back();
}

bool visited[MAX];
int colorsize[MAX];
void color_dfs(int v, int p)
{
	if(visited[v]) return;
	visited[v] = true;
	int size = 1;
	for(int i = 0; i < GC[v].size(); i++)
	{
		int w = GC[v][i];
		if(w == p) continue;
		dfs(w, v, 1);
		size += colorsize[w];
	}
	colorsize[v] = size;
}

int numcolor[MAX];
vector< vector<int> > colorfreq[MAX];
vector<int> ans[MAX];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i < MAX; i++) numcolor[i] = 0;
	for(int i = 1; i <= N; i++)
	{
		cin >> color[i];
		numcolor[color[i]]++;
	}
	for(int c = 1; c < MAX; c++)
	{
		colorfreq[c] = vector< vector<int> >(numcolor[c] + 1);
		ans[c] = vector<int>(numcolor[c] + 1);
	}
	for(int e = 1; e <= N-1; e++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1, -1);
	for(int i = 1; i <= N; i++) visited[i] = false;
	for(int i = 1; i <= N; i++) color_dfs(i, -1);
	for(int i = 1; i <= N; i++)
	{
		int c = color[i], s = colorsize[i];
		colorfreq[c][s].push_back(i);
	}
	for(int c = 1; c < MAX; c++)
	{
		for(int s = 1; s <= numcolor[c]; s++)
		{
			if(colorfreq[c][s].empty()) ans[c][s] = 0;
			else
			{
				int total = depth[colorfreq[c][s][0]];
				for(int i = 1; i < colorfreq[c][s].size(); i++)
				{
					int u = colorfreq[c][s][i-1], v = colorfreq[c][s][i];
					int a = G.lca(u, v);
					total += depth[v] - depth[a];
				}
				ans[c][s] = total;
			}
		}
	}
	for(int i = 1; i <= N; i++) printf("%d %d %d\n",i,color[i],colorsize[i]);
	for(int q = 0; q < M; q++)
	{
		int c, s;
		cin >> c >> s;
		if(s > numcolor[c]) cout << 0 << '\n';
		else cout << ans[c][s] << '\n';
	}
	return 0;
}
