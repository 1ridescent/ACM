#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
#define MOD(x) ((x) % 1000000007);

int N, K, D;

ll dp[105][105][105];

int main()
{
	cin >> N >> K >> D;
	memset(dp, 0, sizeof(dp));
	for(int d = 1; d <= K; d++) dp[1][d][d] = 1;
	for(int n = 2; n <= N; n++)
	{
		for(int s = 1; s <= N; s++)
		{
			for(int d = 1; d <= K; d++)
			{
				for(int m = 1; m <= K; m++)
				{
					if(s - d >= 0) dp[n][s][max(m, d)] = MOD(dp[n][s][max(m, d)] + dp[n - 1][s - d][m]);
				}
			}
		}
	}
	ll total = 0;
	for(int n = 1; n <= N; n++)
	{
		for(int m = D; m <= K; m++)
		{
			total = MOD(total + dp[n][N][m]);
		}
	}
	cout << total;
}
