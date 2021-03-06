#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
int A[505];
bool vis[505][505];
ll dp[505][505];

ll calc(int l, int r)
{
	if(l > r) return 1;
	if(vis[l][r]) return dp[l][r];
	ll res = calc(l + 1, r);
	for(int i = l + 1; i <= r; i++)
		if(A[i] > A[l])
			res = (res + calc(l + 1, i - 1) * calc(i, r)) % 1000000007;
	vis[l][r] = true;
	dp[l][r] = res;
	//printf("dp[%d][%d] = %d\n", l, r, (int)res);
	return res;
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i];
	cout << calc(2, N) << endl;
}
