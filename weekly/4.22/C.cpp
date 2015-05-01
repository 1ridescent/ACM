#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

int N;
ll C;
pair<ll, ll> P[2005];
#define x first
#define y second
#define SQ(x) ((x) * (x))
ll cost(int u, int v)
{
	ll d = SQ(P[u].x - P[v].x) + SQ(P[u].y - P[v].y);
	if(d < C) return inf;
	return d;
}

bool vis[2005];
ll dist[2005];

int main()
{
	cin >> N >> C;
	for(int i = 0; i < N; i++)
		cin >> P[i].x >> P[i].y;
	ll total = 0;
	for(int i = 0; i < N; i++) dist[i] = inf;
	dist[0] = 0;
	for(int t = 0; t < N; t++)
	{
		ll best = inf + 10, besti = -1;
		for(int i = 0; i < N; i++)
			if(!vis[i] && dist[i] < best)
				best = dist[i], besti = i;
		assert(besti != -1);
		//cout << best << ' ' << besti << endl;
		total += best;
		vis[besti] = true;
		for(int i = 0; i < N; i++)
			dist[i] = min(dist[i], cost(i, besti));
	}
	cout << (total >= inf ? -1 : total) << endl;
}
