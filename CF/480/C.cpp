#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define MOD(x) (((x) + mod * 100LL) % mod)

ll dp[5050][5050];
ll pref[5050];

int main()
{
	int N, A, B, K;
	cin >> N >> A >> B >> K;

	memset(dp, 0, sizeof(dp));
	for(int i = 1; i <= N; i++)
		if(i != B)
			dp[0][i]++;

	for(int s = 1; s <= K; s++)
	{
		pref[0] = 0;
		for(int i = 1; i <= N; i++)
		{
			pref[i] = MOD(pref[i - 1] + dp[s - 1][i]);
			//cout << s - 1 << ' ' << i << ':' << pref[i] << endl;
		}

		for(int i = 1; i <= N; i++)
		{
			if(i == B) continue;
			int d = abs(i - B) - 1;
			int l = max(1, i - d);
			int r = min(N, i + d);
			dp[s][i] = MOD(pref[r] - pref[l - 1] - dp[s - 1][i]);
			//cout << s << ' ' << i << ' ' << dp[s][i] << endl;
		}
	}
	cout << dp[K][A];
}
