#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <cstdio>

using namespace std;

typedef long long ll;
#define left Left

int N, K, A, B;

vector<int> G[500500];

ll D[500500];
bool visited[500500];
priority_queue< pair<ll, int>, vector< pair<ll, int> >, greater< pair<ll, int> > > Q;
map<int, int> left;

void dijkstra()
{
	for(int i = 1; i <= N; i++) left[i] = -1;

	memset(visited, 0, sizeof(visited));
	Q.push( make_pair(0, 1) );
	while(!Q.empty())
	{
		ll d = Q.top().first, v = Q.top().second;
		Q.pop();
		if(v == N)
		{
			cout << d << endl;
			return;
		}
		if(visited[v]) continue;

		visited[v] = true;
		for(int i = 0; i < G[v].size(); i++)
		{
			int w = G[v][i];
			if(!visited[w]) Q.push( make_pair(d + A, w) );
			left[w] = v;
		}

		for(map<int, int>::iterator it = left.begin(); it != left.end(); it++)
		{
			if(it->second != v)
			{
				int w = it->first;
				if(!visited[w]) Q.push( make_pair(d + B, w) );
				left.erase(it);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	scanf("%d %d %d %d", &N, &K, &A, &B);//cin >> N >> K >> A >> B;
	for(int i = 0; i < K; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);//cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dijkstra();
}
