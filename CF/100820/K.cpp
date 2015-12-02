#include <bits/stdc++.h>

using namespace std;

const int MAX = 27777;
struct EulerTour
{
	vector<int> G[MAX];
	bool vis[MAX];
	void add_edge(int u, int v)
	{
		//printf("adding edge %d - %d\n", u, v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	void flood(int u)
	{
		vis[u] = true;
		for(int v : G[u]) if(!vis[v]) flood(v);
	}
	bool has_tour(int s)
	{
		memset(vis, 0, sizeof(vis));
		flood(s);
		bool odd_deg = (G[s].size() % 2);
		for(int i = 0; i < MAX; i++)
		{
			if(s == i)continue;
			if(G[i].size() && !vis[i]) return false;
			if(G[i].size() % 2)
			{
				if(odd_deg) odd_deg = false;
				else return false;
			}
		}
		return true;
	}
};

#define ID(r, c) (100 * (r) + (c))

int N;
char B[33][33];
vector<pair<int, int> > edges;
int numW = 0;
bool same(int r1, int c1, int r2, int c2)
{
	//cout << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << ' ' << r1 + c1 - r2 - c2 << ' ' << r1 - c1 - (r2 - c2) << endl;
	return ((r1 + c1 - r2 - c2) % 4 == 0) && ((r1 - c1 - (r2 - c2)) % 4 == 0);
}
vector<pair<int, int> > good;
bool test(int r, int c)
{
	//printf("testing r=%d c=%d\n", r, c);
	EulerTour ET;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			if(B[i][j] == 'W')
			{
				//printf("at r=%d c=%d\n", i, j);
				if(same(i - 1, j - 1, r, c))
				{
					if(B[i-1][j-1] == '_' && B[i+1][j+1] == '_')
						ET.add_edge(ID(i - 1, j - 1), ID(i + 1, j + 1));
					else return false;
				}
				else if(same(i - 1, j + 1, r, c))
				{
					if(B[i-1][j+1] == '_' && B[i+1][j-1] == '_')
						ET.add_edge(ID(i - 1, j + 1), ID(i + 1, j - 1));
					else return false;
				}
				else
				{
					return false;
				}
			}
	if(ET.has_tour(ID(r, c))) good.push_back(make_pair(r, c));
	//cout << "---\n";
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
		{
			cin >> B[i][j];
			if(B[i][j] == 'W')
			{
				if(i == 1 || i == N || j == 1 || j == N)
				{
					cout << "None\n";
					return 0;
				}
				numW++;
			}
		}
	for(int i =1; i <= N; i++)
		for(int j = 1; j <= N; j++)
		{
			if(B[i][j] == 'B')
			{
				B[i][j] = '_';
				test(i, j);
				B[i][j] = 'B';
			}
		}
	//cout << N << ' ' << good[0].first << ' ' << good[0].second << endl;
	if(good.size() == 0) cout << "None\n";
	else if(good.size() == 1) cout << char('a' - 1 + good[0].second) << N + 1 - good[0].first << endl;
	else cout << "Multiple\n";
}
