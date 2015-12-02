#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

ll dp[105][4];

int main2()
{
	int R, C;
	cin >> R >> C;
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for(int i = 1; i <= R; i++)
	{
		for(int j = 0; j <= 3; j++)
		{
			if(i >= 1 && j != 2)
				dp[i][2] += dp[i - 1][j];
			if(i >= 2 && j != 2 && C % 6 == 0)
				dp[i][2] += 6 * dp[i - 2][j];
			if(i >= 2 && j != 2 && C % 3 == 0)
				dp[i][2] += 3 * dp[i - 2][j];
			if(i >= 3 && j != 2 && C % 4 == 0)
				dp[i][2] += 4 * dp[i - 3][j];

			if(i >= 2 && j != 2 && C == 2)
				dp[i][2] += dp[i - 2][j];
			if(i >= 3 && j != 2 && C == 3)
				dp[i][2] += 3 * dp[i - 3][j];
			if(i >= 4 && j != 2 && C == 2)
				dp[i][2] += 2 * dp[i - 4][j];

			if(i >= 2 && j != 3)
				dp[i][3] += dp[i - 2][j];
		}
		for(int j = 0; j <= 3; j++)
		{
			dp[i][j] %= mod;
			//cout << i << ' ' << j << ' ' << dp[i][j] << endl;
		}
	}
	ll res = 0;
	for(int j = 0; j <= 3; j++)
		res += dp[R][j];
	cout << res % mod << endl;
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		printf("Case #%d: ", t);
		main2();
	}
}
