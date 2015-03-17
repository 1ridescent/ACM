#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e17;

int N, M;
vector<pair<int, ll> > G[100005];
vector<int> P;
bool B[100005];
bool vis[2][100005];
ll D[100005];
int S, T;

void dijkstra()
{
	priority_queue<pair<ll, pair<int, int> > > Q;
	for(int i = 0; i < 100005; i++) D[i] = inf;
	for(int i = 0; i < P.size(); i++)
	{
		int p = P[i];
		Q.push(make_pair(-0, make_pair(0, p)));
	}
	while(!Q.empty())
	{
		ll d = -Q.top().first;
		int b = Q.top().second.first, u = Q.top().second.second;
		Q.pop();
		if(vis[b][u]) continue;
		//cout << "b=" << b <<  " u=" << u << " d=" << d << endl;
		vis[b][u] = true;
		D[u] = min(D[u], d);
		//for(int i = 0; i < N; i++) cout << B[i]; cout << " " << b << endl;
		if(!b && B[u])
			Q.push(make_pair(-d, make_pair(1, u)));
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].first;
			ll w = G[u][i].second;
			if(b) w /= 2;
			Q.push(make_pair(-(d + w), make_pair(b, v)));
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		ll u, v, w;
		cin >> u >> v >> w;
		w *= 2;
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
	int K;
	cin >> K;
	while(K--)
	{
		int p;
		cin >> p;
		P.push_back(p);
	}
	int Q2;
	cin >> Q2;
	while(Q2--)
	{
		int q;
		cin >> q;
		B[q] = true;
	}
	dijkstra();
	//for(int i = 0; i < N; i++) cout << D[i] << ' '; cout << endl;
	cin >> S >> T;
	memset(vis, 0, sizeof(vis));
	priority_queue<pair<ll, int> > Q;
	if(0 < D[S]) Q.push(make_pair(-0, S));
	while(!Q.empty())
	{
		ll d = -Q.top().first;
		int u = Q.top().second;
		Q.pop();
		if(vis[0][u]) continue;
		vis[0][u] = true;
		if(u == T)
		{
			cout << d / 2 << endl;
			return 0;
		}
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].first;
			ll w = G[u][i].second;
			if(d + w < D[v]) Q.push(make_pair(-(d + w), v));
		}
	}
	cout << -1 << endl;
}
