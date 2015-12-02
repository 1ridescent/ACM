#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e18;

ll N, K;
int A[300005];
ll dp[5050][5050];

int main()
{
	cin >> N >> K;
	for(int i = 1; i <= N; i++) cin >> A[i];
	ll len1 = N / K + 1;
	ll num1 = N % K; // N/K+1
	ll len2 = N / K;
	ll num2 = K - num1; // N/K
	assert(len1 * num1 + len2 * num2 == N);
	sort(A + 1, A + N + 1);

	for(int k1 = 0; k1 <= num1; k1++)
		for(int k2 = 0; k2 <= num2; k2++)
			dp[k1][k2] = inf;
	dp[0][0] = 0;
	for(int k1 = 0; k1 <= num1; k1++)
		for(int k2 = 0; k2 <= num2; k2++)
		{
			int len = k1 * len1 + k2 * len2;
			if(k1 > 0) dp[k1][k2] = min(dp[k1][k2], dp[k1 - 1][k2] + (A[len] - A[len - len1 + 1]));
			if(k2 > 0) dp[k1][k2] = min(dp[k1][k2], dp[k1][k2 - 1] + (A[len] - A[len - len2 + 1]));
		}
	cout << dp[num1][num2] << endl;
}
