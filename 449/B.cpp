#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;
const ll INF = (1LL << 60);

struct edge
{
	int v;
	ll w;
	char t;
};

int N, M, K;
vector<edge > G[100005];

bool used[100005];
pair<ll, int> D[100005];
priority_queue<pair<ll, int> > Q;
void dijkstra()
{
	memset(used, 0, sizeof(used));
	for(int i = 1; i <= N; i++) D[i] = make_pair(INF, i);
	Q.push(make_pair(0, 1));
	while(!Q.empty())
	{
		int u = Q.top().second;
		ll d = -Q.top().first;
		Q.pop();
		if(used[u]) continue;
		used[u] = true;
		D[u].first = d;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].v;
			if(!used[v]) Q.push(make_pair(-(d + G[u][i].w), v));
		}
	}
}

pair<ll, int> D2[100005];

int main()
{
	cin >> N >> M >> K;
	for(int i = 0; i < M; i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edge e;
		e.v = v, e.w = w, e.t = 'r';
		G[u].push_back(e);
		e.v = u;
		G[v].push_back(e);
	}
	for(int i = 0; i < K; i++)
	{
		int u = 1, v, w;
		scanf("%d %d", &v, &w);
		edge e;
		e.v = v, e.w = w, e.t = 't';
		G[u].push_back(e);
		e.v = u;
		G[v].push_back(e);
	}
	dijkstra();
	//for(int i = 1; i <= N; i++) cout << D[i].first << ' '; cout << endl;

	memcpy(D2, D, sizeof(D));
	sort(D2 + 1, D2 + 1 + N);
	int num = 0;
	for(int i = 2; i <= N; i++)
	{
		int u = D2[i].second;
		bool needed = true;
		for(int i = 0; i < G[u].size(); i++)
		{
			if(G[u][i].t != 'r') continue;
			int v = G[u][i].v;
			if(D[v].first + G[u][i].w == D[u].first) needed = false;
		}
		num += needed;
	}
	cout << K - num << endl;
	
}
