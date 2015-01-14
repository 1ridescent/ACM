#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
int S[23];
bool dp[24][2005][2005];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> S[i];
	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = true;
	int sum = 0;
	for(int n = 1; n <= N; n++)
	{
		sum += S[n];
		for(int i = 0; i <= 2000; i++)
		{
			for(int j = 0; j <= 2000; j++)
			{
				if(i + S[n] <= 2000) dp[n][i+S[n]][j] |= dp[n-1][i][j]; // add to first
				if(j + S[n] <= 2000) dp[n][i][j+S[n]] |= dp[n-1][i][j]; // add to second
				dp[n][i][j] |= dp[n-1][i][j]; // add to third
			}
		}
	}
	int best = sum;
	for(int i = 0; i <= 2000; i++)
	{
		for(int j = 0; j < 2000; j++)
		{
			if(dp[N][i][j])
			{
				int k = sum-i-j;
				//cout << i << ' ' << j << ' ' << k << endl;
				best = min(best, max(i,max(j,k)));
			}
		}
	}
	cout << best << endl;
	return 0;
}
