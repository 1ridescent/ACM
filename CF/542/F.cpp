#include <bits/stdc++.h>

using namespace std;

int N, T;
vector<int> V[105];

const int inf = 1e9;
int dp[105][1005];

int main()
{
	cin >> N >> T;
	for(int i = 0; i < N; i++)
	{
		int t, q;
		cin >> t >> q;
		V[T - t].push_back(q);
	}
	for(int i = 0; i <= T; i++)
	{
		V[i].push_back(0);
		sort(V[i].begin(), V[i].end(), greater<int>());
	}
	for(int i = 0; i < 105; i++)
		for(int j = 0; j < 1005; j++)
			dp[i][j] = -inf;
	dp[0][0] = V[0].front();
	dp[0][1] = 0;
	int best = V[0].front();
	for(int t = 1; t <= T; t++)
	{
		int add = 0;
		for(int n = 0; n <= V[t].size(); n++)
		{
			if(n) add += V[t][n - 1];
			for(int i = (n + 1) / 2; i <= N; i++)
			{
				int j = min(i * 2 - n, N);
				dp[t][j] = max(dp[t][j], dp[t - 1][i] + add);
			}
		}
		for(int i = 0; i <= N; i++)
			best = max(best, dp[t][i]);
	}
	cout << best;
}
