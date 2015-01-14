#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

int N;
vector<int> G[100005];

ll dp[100005][2]; // [root][num%2]
int size[100005];

int get_size(int v)
{
	size[v] = 1;
	for(int i = 0; i < G[v].size(); i++)
	{
		size[v] += get_size(G[v][i]);
	}
	return size[v];
}

void dfs(int v)
{
	for(int i = 0; i < G[v].size(); i++)
		dfs(G[v][i]);

	ll total[2][2][2]; // [total%2][all0?][all1?]
	memset(total, 0, sizeof(total));
	total[0][1][1] = 1;

	for(int i = 0; i < G[v].size(); i++)
	{
		int w = G[v][i];
		ll total2[2][2][2];
		memcpy(total2, total, sizeof(total));

			total2[0][0][0] += total[0][0][0] * dp[w][0];
			total2[0][0][0] += total[0][0][1] * dp[w][0];
			total2[0][1][0] += total[0][1][0] * dp[w][0];
			total2[0][1][0] += total[0][1][1] * dp[w][0];

			total2[0][0][0] += total[1][0][0] * dp[w][1];
			total2[0][0][0] += total[1][1][0] * dp[w][1];
			total2[0][0][1] += total[1][0][1] * dp[w][1];
			total2[0][0][1] += total[1][1][1] * dp[w][1];

			total2[1][0][0] += total[0][0][0] * dp[w][1];
			total2[1][0][0] += total[0][1][0] * dp[w][1];
			total2[1][0][1] += total[0][0][1] * dp[w][1];
			total2[1][0][1] += total[0][1][1] * dp[w][1];

			total2[1][0][0] += total[1][0][0] * dp[w][0];
			total2[1][0][0] += total[1][0][1] * dp[w][0];
			total2[1][1][0] += total[1][1][0] * dp[w][0];
			total2[1][1][0] += total[1][1][1] * dp[w][0];

			for(int b = 0; b < 8; b++)
				total[!(b & 4)][!(b & 2)][!(b & 1)] = total2[!(b & 4)][!(b & 2)][!(b & 1)] % mod;

	}

	dp[v][0] = dp[v][1] = 0;
	for(int t = 0; t <= 1; t++)
	{
		for(int b = 0; b < 4; b++)
			dp[v][t] += 2 * total[t][b / 2][b % 2];
	}

	dp[v][0] -= total[0][1][0];
	dp[v][0] -= total[0][1][1];
	dp[v][1] -= total[1][0][1];
	dp[v][1] -= total[1][1][1];

	dp[v][0] %= mod;
	dp[v][1] %= mod;

	swap(dp[v][0], dp[v][1]);
	/*

	total[0][0] = 1;
	for(int i = 0; i < G[v].size(); i++)
	{
		int w = G[v][i];
		ll total2[2][2];
		memcpy(total2, total, sizeof(total));
		for(int b = 0; b <= 1; b++)
		{
			total2[b][0] += (total2[!b][0] * dp[w][0] + total2[!b][1] * dp[w][1]);
			total2[b][1] += (total2[!b][0] * dp[w][1] + total2[!b][1] * dp[w][0]);
		}

		for(int b = 0; b < 4; b++)
			total[b / 2][b % 2] = total2[b / 2][b % 2] % mod;
	}
	total[0] *= 2, total[1] *= 2; // forward and backward

	ll overlap_even = 0;
	ll overlap_odd = 0;
	for(int i = 0; i < G[v].size(); i++)
	{
		int w = G[v][i];
		overlap_even = (overlap_even * dp[w][0]) % mod;
		overlap_odd = (overlap_odd * dp[w][1]) % mod;
	}
	total[0] = (total[0] - overlap_even + mod) % mod;
	if(G[v].size() % 2 == 1)
		total[1] = (total[1] - overlap_odd + mod) % mod;

	dp[v][0] = total[0];
	dp[v][1] = total[1];*/
}

int main()
{
	cin >> N;
	for(int i = 2; i <= N; i++)
	{
		int p;
		cin >> p;
		G[p].push_back(i);
	}

	get_size(1);

	dfs(1);

	cout << (dp[1][0] + dp[1][1]) % mod;
}
