#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e11;

int N;
ll A[1005];
int s0;

bool vis[1005][1005];
vector<pair<pair<int, int>, ll> > G[1005][1005];

priority_queue<pair<ll, pair<int, int> > > Q;
ll dijkstra()
{
	Q.push(make_pair(-0, make_pair(s0, s0)));
	while(!Q.empty())
	{
		ll d = -Q.top().first;
		pair<int, int> u = Q.top().second;
		Q.pop();
		if(vis[u.first][u.second]) continue;
		//cout << u.first << ' ' << u.second << ' ' << d << endl;
		vis[u.first][u.second] = true;
		if(abs(u.first - u.second) == N - 1) return d;
		for(int i = 0; i < G[u.first][u.second].size(); i++)
		{
			ll l = G[u.first][u.second][i].second;
			Q.push(make_pair(-(d + l), G[u.first][u.second][i].first));
		}
	}
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> A[i];
	A[N++] = 0;
	sort(A, A + N);
	for(int i = 0; i < N; i++) if(A[i] == 0) s0 = i;
	for(int s = 0; s <= s0; s++)
		for(int t = s0; t < N; t++)
		{
			int l = N - (t - s + 1);
			if(s > 0)
				G[s][t].push_back(make_pair(make_pair(s - 1, t), l * (A[s] - A[s - 1])));
			if(t < N - 1)
				G[t][s].push_back(make_pair(make_pair(t + 1, s), l * (A[t + 1] - A[t])));
			G[s][t].push_back(make_pair(make_pair(t, s), l * (A[t] - A[s])));
			G[t][s].push_back(make_pair(make_pair(s, t), l * (A[t] - A[s])));
		}
	cout << dijkstra() << endl;
}
