#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e15;

int N;
ll A[15][15];
vector<int> R[15];

int vis[15];
void flood(int u, int m)
{
	vis[u] = m;
	for(int i = 0; i < R[u].size(); i++)
	{
		int v = R[u][i];
		if(!vis[v]) flood(v, m);
	}
}

int deg[15];

int num_cmpt = 0;
int cmpt[15];
int init[15];

vector<pair<ll, pair<int, int> > > G[1 << 7][1 << 13];
priority_queue<pair<ll, pair<int, int> > > Q;
bool vis2[1 << 7][1 << 13];

int main()
{
	int K;
	cin >> N >> K;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			A[i][j] = inf;
	ll sum = 0;
	deg[0] += 2;
	while(K--)
	{
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--, b--;
		R[a].push_back(b);
		R[b].push_back(a);
		A[a][b] = min(A[a][b], c);
		A[b][a] = min(A[b][a], c);
		deg[a]++;
		deg[b]++;
		sum += c;
	}
	cin >> K;
	while(K--)
	{
		int a, b;
		ll c;
		cin >> a >> b >> c;
		a--, b--;
		A[a][b] = min(A[a][b], c);
		A[b][a] = min(A[b][a], c);
	}
	for(int k = 1; k < N; k++)
		if(!deg[k])
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
	for(int i = 0; i < N; i++)
		if(deg[i] && !vis[i])
		{
			flood(i, i + 1);
			for(int j = 0; j < N; j++)
				if(vis[j] == i + 1)
					cmpt[j] = num_cmpt;
			num_cmpt++;
		}
	for(int c = 0; c < num_cmpt; c++)
	{
		int mask = 0;
		for(int i = 0; i < N; i++)
			if(deg[i] && cmpt[i] == c && deg[i] % 2)
				mask |= (1 << i);
		init[c] = mask;
	}
	for(int b = 0; b < (1 << num_cmpt); b++)
	{
		if(!(b & (1 << cmpt[0]))) continue;
		int mask = 0;
		for(int i = 0; i < N; i++)
			if(deg[i])
				if(b & (1 << cmpt[i])) mask |= (1 << i);
		for(int m = 0; m < (1 << N); m++)
		{
			if((m | mask) == mask)
			{
				for(int i = 0; i < N; i++)
					for(int j = 0; j < N; j++)
						if(deg[i] && deg[j] && (b & (1 << cmpt[i])) && (b & (1 << cmpt[j]))) // within
							G[b][m].push_back(make_pair(A[i][j], make_pair(b, m ^ (1 << i) ^ (1 << j))));
				for(int i = 0; i < N; i++)
					for(int j = 0; j < N; j++)
					{
						int c = cmpt[j];
						if(deg[i] && deg[j] && (b & (1 << cmpt[i])) && !(b & (1 << c)))
							G[b][m].push_back(make_pair(A[i][j], make_pair(b | (1 << c), m ^ init[c] ^ (1 << i) ^ (1 << j))));
					}
			}
		}
	}
	Q.push(make_pair(-0, make_pair(1 << cmpt[0], init[cmpt[0]])));
	while(!Q.empty())
	{
		ll d = -Q.top().first;
		int b = Q.top().second.first;
		int m = Q.top().second.second;
		Q.pop();
		if(vis2[b][m]) continue;
		vis2[b][m] = true;
		//cout << b << ' ' << m << ' ' << num_cmpt << endl;
		if(b == (1 << num_cmpt) - 1 && m == 0)
		{
			//assert(sum + d < inf);
			cout << sum + d << endl;
			return 0;
		}
		for(int i = 0; i < G[b][m].size(); i++)
		{
			ll d2 = d + G[b][m][i].first;
			int b2 = G[b][m][i].second.first;
			int m2 = G[b][m][i].second.second;
			if(!vis2[b2][m2])
				Q.push(make_pair(-d2, make_pair(b2, m2)));
		}
	}
}
