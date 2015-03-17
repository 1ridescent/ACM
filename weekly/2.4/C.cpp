#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
int A[100005];
vector<int> G[100005];
priority_queue<pair<ll, int> > Q;
int cnt[100005];
bool vis[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		cnt[b]++;
	}
	for(int i = 1; i <= N; i++)
		if(!cnt[i])
		{
			Q.push(make_pair(-A[i], i));
			//cout << i << endl;
		}
	ll ans = 0;
	while(!Q.empty())
	{
		pair<ll, int> p = Q.top();
		Q.pop();
		ll t = -(p.first);
		int u = p.second;
		//cout << t << ' ' << u << endl;
		if(vis[u]) continue;
		vis[u] = true;
		ans = max(ans, t);
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			cnt[v]--;
			//cout << "cnt of " << v << " is " << cnt[v] << endl;
			if(!cnt[v]) Q.push(make_pair(-(t + A[v]), v));
		}
	}
	cout << ans << endl;
}
