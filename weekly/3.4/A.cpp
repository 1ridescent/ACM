#include <bits/stdc++.h>

using namespace std;

int N;
int G[12][3];
int dp[1 << 12];

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < 3; j++)
		{
			cin >> G[i][j];
			G[i][j]--;
		}
	for(int i = 1; i < (1 << N); i++) dp[i] = 1e8;
	for(int b = 0; b < (1 << N); b++)
	{
		int s = 0;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < 3; j++)
				s += ((!!(b & (1 << i))) ^ (!!(b & (1 << G[i][j]))));
		for(int i = 0; i < N; i++)
			if(!(b & (1 << i)))
			{
				int b2 = b | (1 << i);
				dp[b2] = min(dp[b2], dp[b] + s);
			}
	}
	cout << dp[(1 << N) - 1] / 2 << endl;
}
