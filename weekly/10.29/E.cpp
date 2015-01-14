#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

int N, L, R;

ll choose[5050][5050];
ll dp[5050][5050];

void pre()
{
	memset(choose, 0, sizeof(choose));
	for(int n = 0; n <= 5005; n++)
	{
		choose[n][0] = choose[n][n] = 1;
		for(int k = 1; k < n; k++)
			choose[n][k] = (choose[n - 1][k - 1] + choose[n - 1][k]) % mod;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	pre();
	while(true)
	{
		cin >> N >> L >> R;
		if(!N) break;
		memset(dp, 0, sizeof(dp));
		dp[1][0] = 1;
		for(ll i = 2; i <= N; i++)
		{
			dp[i][0] = ((i - 2) * dp[i - 1][0]) % mod;
			for(ll n = 1; n <= N; n++)
			{
				dp[i][n] = ((i - 2) * dp[i - 1][n] + dp[i - 1][n - 1]) % mod;
			}
		}
		cout << (dp[N][L + R - 2] * choose[L + R - 2][L - 1]) % mod << '\n';
	}
}
