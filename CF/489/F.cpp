#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

int N, M, mod;

ll dp[2][505][505];

char B[505][505];
int cnt[505];

int main()
{
	cin >> N >> M >> mod;
	memset(cnt, 0, sizeof(cnt));
	for(int i = 1; i <= M; i++)
	{
		for(int j = 1; j <= N; j++)
		{
			cin >> B[i][j];
			cnt[j] += (B[i][j] == '1');
		}
	}
	memset(dp, 0, sizeof(dp));
	int R = N - M;
	dp[0][R][0] = 1;
	for(int c = 1; c <= N; c++)
	{
		int b = (c & 1);
		memset(dp[b], 0, sizeof(dp[b]));
		for(int i = 0; i <= R; i++)
			for(int j = 0; j <= R - i; j++)
			{
				if(dp[b ^ 1][i][j] == 0) continue;//cout << "cnt = " << cnt[c] << endl;
				if(cnt[c] == 2)
					dp[b][i][j] += dp[b ^ 1][i][j];
				else if(cnt[c] == 1)
				{
					// 0 -> 1
					if(i > 0)
						dp[b][i - 1][j + 1] += dp[b ^ 1][i][j] * i;
					// 1 -> 2
					if(j > 0)
						dp[b][i][j - 1] += dp[b ^ 1][i][j] * j;
				}
				else if(cnt[c] == 0)
				{
					// (0 -> 1) x 2
					if(i > 1)
						dp[b][i - 2][j + 2] += dp[b ^ 1][i][j] * (i * (i - 1) / 2);
					// (0 -> 1) + (1 -> 2)
					if(i > 0 && j > 0)
						dp[b][i - 1][j] += dp[b ^ 1][i][j] * i * j;
					// (1 -> 2) x 2
					if(j > 1)
						dp[b][i][j - 2] += dp[b ^ 1][i][j] * (j * (j - 1) / 2);
				}
			}
		for(int i = 0; i <= R; i++)
			for(int j = 0; j <= R - i; j++)
				dp[b][i][j] %= mod;
	}
	cout << dp[N & 1][0][0];
}
