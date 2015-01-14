#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int inf = 255;

int N;
int L[20];
int dp[1 << 20][10];

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> L[i];
	for(int i = 0; i < (1 << 20); i++)
		for(int j = 0; j < 10; j++)
			dp[i][j] = inf;

	dp[0][0] = 0;
	for(int b = 0; b < (1 << 20); b++)
	{
		for(int l = 0; l <= 7; l++)
		{
			//if(dp[b][l] < inf) cout << b << ' ' << l << ' ' << dp[b][l] << endl;
			for(int i = 0; i < N; i++)
			{
				int b2 = (b | (1 << i));
				int l2 = max(1, L[i] - l) - 1;
				dp[b2][l2] = min(dp[b2][l2], dp[b][l] + l + 1);
			}
		}
	}

	int b = (1 << N) - 1;
	int best = inf;
	for(int l = 0; l <= 7; l++)
		best = min(best, dp[b][l] + l);
	cout << best << endl;
}
