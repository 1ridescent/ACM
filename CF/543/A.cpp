#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll mod;

int N, M, B;

ll dp[505][505];

int main()
{
	cin >> N >> M >> B >> mod;
	dp[0][0] = 1;
	for(int t = 0; t < N; t++)
	{
		int x;
		cin >> x;
		for(int l = 1; l <= 502; l++)
			for(int b = x; b <= 502; b++)
			{
				dp[l][b] = (dp[l][b] + dp[l - 1][b - x]) % mod;
			}
	}
	ll total = 0;
	for(int b = 0; b <= B; b++)
		total += dp[M][b];
	cout << total % mod << endl;
}
