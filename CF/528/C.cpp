#include <bits/stdc++.h>

using namespace std;

int N, M;
set<pair<int, int> > G[100005];

vector<int> tour;
void dfs(int u)
{
	while(!G[u].empty())
	{
		int v = (G[u].begin())->first, i = (G[u].begin())->second;
		G[u].erase(make_pair(v, i));
		G[v].erase(G[v].lower_bound(make_pair(u, -1)));
		dfs(v);
	}
	tour.push_back(u);
}
vector<pair<int, int> > added;
vector<int> odd;
void add_edge(int u, int v)
{
	G[u].insert(make_pair(v, 1000000 + added.size() * 2 + 1));
	G[v].insert(make_pair(u, 1000000 + added.size() * 2));
	added.push_back(make_pair(u, v));
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].insert(make_pair(b, 2 * i + 1));
		G[b].insert(make_pair(a, 2 * i + 2));
	}
	for(int i = 1; i <= N; i++)
	{
		//cout << i << ' ' << G[i].size() << endl;
		if(G[i].size() % 2 == 1)
		{
			odd.push_back(i);
			//cout << "added " << i << endl;
		}
	}
	assert(odd.size() % 2 == 0);
	for(int i = 0; i < odd.size(); i += 2)
	{
		int u = odd[i], v = odd[i + 1];
		add_edge(u, v);
	}
	if((M + added.size()) % 2 == 1)
		add_edge(1, 1);
	dfs(1);
	//for(int i = 0; i < tour.size(); i++) cout << tour[i] << ' ';
	cout << M + added.size() << '\n';
	for(int i = 0; i < tour.size() - 1; i++)
	{
		int u = tour[i], v = tour[i + 1];
		if(i % 2) swap(u, v);
		cout << u << ' ' << v << '\n';
	}
}
