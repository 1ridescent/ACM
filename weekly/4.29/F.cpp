#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <queue>

using namespace std;

typedef long long ll;
const ll inf = 1e12;

int N;
ll K;
ll H[22], W[22], S[22];
ll dp[1 << 20];

int main()
{
	cin >> N >> K;
	for(int i = 0; i < N; i++)
		cin >> H[i] >> W[i] >> S[i];
	memset(dp, -1, sizeof(dp));
	dp[0] = inf;
	ll best = -1;
	for(int b = 0; b < (1 << N); b++)
	{
		ll h = 0;
		for(int i = 0; i < N; i++)
			if(b & (1 << i))
				h += H[i];
		if(h >= K) best = max(best, dp[b]);
		for(int i = 0; i < N; i++)
			if(!(b & (1 << i)))
			{
				int b2 = b + (1 << i);
				dp[b2] = max(dp[b2], min(dp[b] - W[i], S[i]));
			}
	}
	if(best < 0) printf("Mark is too tall\n");
	else cout << best << endl;
}
