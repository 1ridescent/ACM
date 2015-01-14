#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct edge
{
	int v, id;
	edge(int v2, int id2)
	{
		v = v2, id = id2;
	}
};

const int MAX = 300300;
struct EulerTour
{
	vector<edge> G[MAX];
	bool used[MAX];
	vector<int> tour;
	void euler_tour(int v)
	{
		for(int i = 0; i < G[v].size(); i++)
		{
			//cout << v << " -> " << G[v][i].v << endl;
			if(used[G[v][i].id]) continue;
			used[G[v][i].id] = true;
			euler_tour(G[v][i].v);
		}
		tour.push_back(v);
	}
};

void print(vector<int> V)
{
	for(int i = 0; i < V.size(); i++)
	{
		if(i > 0) cout << ' ';
		cout << V[i];
	}
	cout << endl;
}

int N, M;
vector<edge> G[MAX];
bool processed[MAX];

EulerTour ET;

vector<int> res;

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= M; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(edge(v, i));
		G[v].push_back(edge(u, i));
	}

	memset(processed, 0, sizeof(processed));
	int vid = N, eid = M;
	for(int v = 1; v <= N; v++)
	{
		if(processed[v]) continue;
		if(G[v].size() == 2)
		{
			ET.G[v] = G[v];
			continue;
		}
		if(G[v].size() % 2 == 1)
		{
			cout << "-1";
			return 0;
		}
		vector<int> clique;
		clique.push_back(v);
		for(int i = 0; i < G[v].size(); i++)
		{
			int w = G[v][i].v;
			if(G[w].size() != 2) clique.push_back(w);
		}

		vid++;
		for(int i = 0; i < clique.size(); i++)
		{
			int v = clique[i];
			ET.G[vid].push_back(edge(v, ++eid));
			ET.G[v].push_back(edge(vid, eid));
			for(int j = 0; j < G[v].size(); j++)
			{
				int w = G[v][j].v;
				if(G[w].size() == 2) ET.G[v].push_back(G[v][j]);
			}
			processed[clique[i]] = true;
		}
		//print(clique);
	}

	int s = 0;
	while(ET.G[s].empty()) s++;
	ET.euler_tour(s);
	for(int i = 0; i < ET.tour.size(); i++)
	{
		if(ET.tour[i] <= N) res.push_back(ET.tour[i]);
	}
	res.pop_back();
	for(int i = 0; i < res.size(); i++)
	{
		if(i > 0) cout << ' ';
		cout << res[i];
	}
}
