#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define MOD(x) (((x) + mod) % mod)

ll pow2[505];

int N, K;
ll dp[505][505];
ll temp[505][505];

void pre()
{
	pow2[0] = 1;
	for(int i = 1; i <= 500; i++) pow2[i] = MOD(2 * pow2[i - 1]);
}

int main()
{
	pre();

	cin >> N >> K;
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for(int pos = 1; pos <= N; pos++)
	{
		memset(temp, 0, sizeof(temp));
		temp[0][0] = 1;
		for(int num = 1; num <= K; num++)
		{
			ll sum = 0;
			ll weighted_sum = 0;
			for(int last = 0; last <= pos; last++) // don't add
			{
				temp[num][last] = MOD(temp[num][last] + pow2[last] * dp[num][last]);
			}
			for(int last = 0; last <= pos; last++) // add
			{
				temp[num][pos] = MOD(temp[num][pos] + MOD(pow2[pos] - pow2[last]) * dp[num - 1][last]);
			}
		}
		memcpy(dp, temp, sizeof(temp));
	}
	ll total = 0;
	for(int last = 0; last <= N; last++) total = MOD(total + dp[K][last]);
	cout << total << endl;
	return 0;
}
