#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>

using namespace std;

const int MAX = 5050;

int N;
vector<int> G[MAX];
bitset<MAX> B[MAX];

bool visited[MAX];
void dfs(int v)
{
	visited[v] = true;
	B[v].set(v);
	for(int i = 0; i < G[v].size(); i++)
	{
		int w = G[v][i];
		if(!visited[w]) dfs(w);
		B[v] |= B[w];
	}
}

int main()
{
	cin >> N;
	for(int v = 1; v <= N - 1; v++)
	{
		int K;
		cin >> K;
		for(int k = 0; k < K; k++)
		{
			int w;
			cin >> w;
			G[v].push_back(w);
		}
	}

	memset(visited, 0, sizeof(visited));
	dfs(1);

	for(int v = 1; v <= N; v++)
	{
		cout << v << ' ' << B[v].count() << endl;
	}
	return 0;
}
