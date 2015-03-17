#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000009;

ll power(ll b, int e)
{
	if(e == 0) return 1;
	ll res = power(b, e / 2);
	res = (res * res) % mod;
	if(e % 2 == 1) res = (res * b) % mod;
	return res;
}
ll inv(ll b)
{
	return power(b, mod - 2);
}

int N;
int in[105];
vector<int> T[105];

void input()
{
	set<int> G0[105];
	set<int> G[105];
	int M;
	cin >> N >> M;
	while(M--)
	{
		int a, b;
		cin >> a >> b;
		G0[a].insert(b);
		G0[b].insert(a);
		G[a].insert(b);
		G[b].insert(a);
	}
	for(int t = 1; ; t++)
	{
		bool found = false;
		for(int i = 1; i <= N; i++)
		{
			if(in[i]) continue;
			//cout << "size " << i << " = " << G[i].size() << endl;
			if(G[i].size() <= 1)
			{
				//cout << i << " at " << t << endl;
				found = true;
				in[i] = t++;
				for(int j = 1; j <= N; j++)
					G[j].erase(i);
			}
		}
		if(!found) break;
	}
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			if(G0[i].count(j) && in[i] && in[j])
			{
				cout << i << " -> " << j << endl;
				T[i].push_back(j);
			}
}

ll choose[105][105];
void precompute()
{
	choose[0][0] = 1;
	for(int i = 1; i <= 103; i++)
	{
		choose[i][0] = choose[i][i] = 1;
		for(int j = 1; j < i; j++)
			choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
	}
}

int size[105];
ll dp[105][105];
bool vis[105];
void dfs(int u, int p)
{
	if(vis[u]) return;
	vis[u] = true;
	size[u] = 1;
	for(int i = 0; i < T[u].size(); i++)
	{
		int v = T[u][i];
		if(v == p) continue;
		dfs(v, u);
		size[u] += size[v];
	}
	//cout << "size " << u << " = " << size[u] << endl;
	ll temp[105];
	ll temp2[105];
	memset(temp, 0, sizeof(temp));
	temp[0] = 1;
	for(int i = 0; i < T[u].size(); i++)
	{
		int v = T[u][i];
		if(v == p) continue;
		memset(temp2, 0, sizeof(temp2));
		for(int a = 0; a <= 100; a++)
			for(int b = 0; b <= 100 - a; b++)
			{
				temp2[a + b] = (temp2[a + b] + choose[a + b][a] * ((temp[a] * dp[v][b]) % mod)) % mod;
			}
		memcpy(temp, temp2, sizeof(temp));
	}
	assert(temp[size[u]] == 0);
	temp[size[u]] = temp[size[u] - 1];
	memcpy(dp[u], temp, sizeof(temp));
}
void compute(int u)
{
	memset(vis, 0, sizeof(vis));
	dfs(u, -1);
	//cout << u << ": "; for(int i = 0; i <= size[u]; i++) cout << dp[u][i] << ' '; cout << endl;
}

int root[105];

ll total[105];

int main()
{
	input();
	precompute();
	//for(int i = 1; i <= N; i++) compute(i);
	//for(int u = 1; u <= 3; u++) for(int i = 0; i <= 3; i++) cout << dp[u][i] << " \n"[i == 3];

	total[0] = 1;
	for(int r = 1; r <= N; r++)
	{
		//cout << "d\n";
		if(root[r]) continue;
		if(!in[r]) continue;
		ll temp[105];
		memset(temp, 0, sizeof(temp));
		compute(r);
		int s = size[r];
		for(int i = 1; i <= N; i++)
			if(vis[i])
				root[i] = r;
		for(int u = 1; u <= N; u++)
		{
			if(root[u] == r)
			{
				compute(u);
				for(int k = 0; k <= s; k++) temp[k] = (temp[k] + dp[u][k]) % mod;
			}
		}
		for(int k = 0; k < s; k++) temp[k] = (temp[k] * inv(s - k)) % mod;
		//for(int k = 0; k <= s; k++) cout << temp[k] << ' '; cout << endl;

		//cout << "g\n";
		ll total2[105];
		memset(total2, 0, sizeof(total2));
		for(int a = 0; a <= 100; a++)
			for(int b = 0; b <= 100; b++)
				total2[a + b] = (total2[a + b] + choose[a + b][a] * ((temp[a] * total[b]) % mod)) % mod;
		memcpy(total, total2, sizeof(total));
	}
	//for(int k = 0; k <= N; k++) cout << total[k] << '\n';
}
