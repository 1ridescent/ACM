#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
const ll INF = (1LL << 55);

ll val[1000100][3];
ll dp[1000100][8];

int main()
{
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	memset(dp, 0, sizeof(dp));
	memset(val, 0, sizeof(val));
	for(int i = 1; i <= N; i++) cin >> val[i][0] >> val[i][1] >> val[i][2];

	ll best = 0;
	for(int i = 1; i <= N; i++)
	{
		for(int b = 0; b < 8; b++)
		{
			if(i == 1 && (b & 4)) continue;
			if(i == N && (b & 1)) continue;
			dp[i][b] = max(dp[i - 1][b / 2], dp[i - 1][b / 2 + 4]);
			int cnt = 0;
			if(b & 4) cnt++;
			if(b & 1) cnt++;
			if(cnt == 0) dp[i][b] += val[i][0];
			else if(cnt == 1) dp[i][b] += val[i][1];
			else dp[i][b] += val[i][2];
			best = max(best, dp[i][b]);
		}
	}

	cout << best << '\n';
}
