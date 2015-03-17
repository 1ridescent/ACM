#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll dp[1 << 15][15];

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int N, K;
		cin >> N >> K;
		memset(dp, 0, sizeof(dp));
		for(int i = 0; i < N; i++) dp[1 << i][i] = 1;
		for(int b = 1; b < (1 << N); b++)
			for(int s = 0; s < N; s++)
				for(int t = 0; t < N; t++)
				{
					if(abs(s - t) <= K && !(b & (1 << t)))
						dp[b | (1 << t)][t] += dp[b][s];
				}
		ll res = 0;
		for(int i = 0; i < N; i++) res += dp[(1 << N) - 1][i];
		cout << res << endl;
	}
}
