#include <bits/stdc++.h>

using namespace std;

double dp[2005][2005];

int N;
double P;
int T;

int main()
{
	cin >> N >> P >> T;
	dp[0][0] = 1;
	for(int n = 0; n <= 2002; n++)
		for(int t = 0; t <= 2002; t++)
		{
			dp[n + 1][t + 1] += dp[n][t] * P;
			dp[n][t + 1] += dp[n][t] * (1 - P);
		}
	double ans = 0;
	for(int n = 0; n <= 2002; n++)
		ans += min(n, N) * dp[n][T];
	printf("%.9f\n", ans);
}
