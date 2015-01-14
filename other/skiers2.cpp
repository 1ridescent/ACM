#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N;
vector<int> G[5050];
int next[5050];
bool visited[5050];

bool must(int u, int v)
{
	while(v != N)
	{
		if(!visited[v]) return true;
		u = v;
		v = G[v].back();
	}
	return false;
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N - 1; i++)
	{
		int K;
		cin >> K;
		for(int k = 0; k < K; k++)
		{
			int v;
			cin >> v;
			G[i].push_back(v);
		}
		next[i] = 0;
	}

	memset(visited, 0, sizeof(visited));
	visited[N] = true;
	int cnt = 0;
	while(true)
	{
		int u = 1;
		while(u != N)
		{
			cout << u << ' ';
			if(!must(u, G[u][next[u]]))
			{
				if(next[u] == G[u].size() - 1)
				{
					if(u == 1)
					{
						cout << cnt << endl;
						return 0;
					}
				}
				else next[u]++;
			}
			visited[u] = true;
			u = G[u][next[u]];
		}
		cout << N << endl;
		cnt++;
	}
}
