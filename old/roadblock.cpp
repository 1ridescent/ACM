#include <iostream>

using namespace std;

const int INF = 234234234;

int N, M;
int G[105][105];

bool visited[105];
int D[105];
int dijkstra()
{
	for(int i = 1; i <= N; i++) visited[i] = false;
	for(int i = 1; i <= N; i++) D[i] = INF;
	D[1] = 0;
	for(int t = 1; t <= N-1; t++)
	{
		int best = INF, besti = -1;
		for(int i = 1; i <= N; i++)
		{
			if(!visited[i] && D[i] < best)
			{
				best = D[i];
				besti = i;
			}
		}
		visited[besti] = true;
		for(int j = 1; j <= N; j++)
		{
			if(!visited[j]) D[j] = min(D[j], D[besti] + G[besti][j]);
		}
	}
	return D[N];
}

int main()
{
	for(int i = 0; i < 105; i++) for(int j = 0; j < 105; j++) G[i][j] = INF;
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		G[a][b] = min(G[a][b], c);
		G[b][a] = min(G[b][a], c);
	}
	int init = dijkstra();
	int best = init;
	for(int i = 1; i <= N; i++)
	{
		for(int j = i+1; j <= N; j++)
		{
			int add = G[i][j];
			G[i][j] += add;
			G[j][i] += add;
			best = max(best, dijkstra());
			G[i][j] -= add;
			G[j][i] -= add;
		}
	}
	cout << best - init << endl;
	return 0;
}
