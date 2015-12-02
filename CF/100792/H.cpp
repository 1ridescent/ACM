#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll A[100005];
ll dp[100005][525]; // dp[len][num removed]

int get_num(char c)
{
	if('0' <= c && c <= '9') return (c - '0');
	return 10 + (c - 'A');
}
int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		char c1, c2;
		cin >> c1 >> c2;
		A[i] = get_num(c1) * 16 + get_num(c2);
	}
	for(int i = 1; i <= N; i++)
	{
		for(int s = 0; s <= 520 && s < i; s++)
		{
			dp[i][s] = dp[i - 1][s] + ((i - 1 - s) ^ A[i]);
			if(s > 0) dp[i][s] = max(dp[i][s], dp[i - 1][s - 1]);
		}
	}
	ll ans = 0;
	for(int s = 0; s <= 520; s++)
		ans = max(ans, dp[N][s]);
	cout << ans;
}
