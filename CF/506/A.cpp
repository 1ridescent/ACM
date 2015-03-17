#include <iostream>
#include <cstring>

using namespace std;

const int inf = 1000000;

int N, D;
int val[30005];
int dp[30005][2005];

int main()
{
	cin >> N >> D;
	memset(val, 0, sizeof(val));
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		val[x]++;
	}
	int l = max(1, D - 1000), r = D + 1000;
	for(int i = 0; i < 30005; i++)
		for(int j = 0; j < 2005; j++)
			dp[i][j] = -inf;
	dp[D][D - l] = val[D];
	int best = 0;
	for(int x = D; x <= 30000; x++)
	{
		for(int d = l; d <= r; d++)
		{
			int v = dp[x][d - l];
			best = max(best, v);
			for(int d2 = max(1, d - 1); d2 <= d + 1; d2++)
				if(x + d2 <= 30000)
					dp[x + d2][d2 - l] = max(dp[x + d2][d2 - l], v + val[x + d2]);
		}

	}
	cout << best;
}
