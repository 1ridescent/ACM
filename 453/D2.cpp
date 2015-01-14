#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ll;
const int MAX = (1 << 20);

int M, P;
ll T;
int E[MAX];
vector<ll> base;

inline int bitcnt(int x)
{
	int res = 0;
	for(int i = 0; i < M; i++)
		if(x & (1 << i)) res++;
	return res;
}

vector<ll> conv(vector<ll> A, vector<ll> B)
{
	ll choose[22][22];
	for(int n = 0; n < 22; n++)
	{
		choose[n][0] = choose[n][n] = 1;
		for(int k = 1; k < n; k++) choose[n][k] = (choose[n - 1][k - 1] + choose[n - 1][k]) % P;
	}
	vector<ll> C(M + 1, 0);
	for(int d = 0; d <= M; d++)
	{
		int s = M - d;
		for(int i = 0; i <= s; i++)
			for(int j = 0; j <= d; j++)
				C[d] = (C[d] + ((choose[s][i] * choose[d][j]) % P) * ((A[i + j] * B[i + (d - j)]) % P)) % P;
	}
	return C;
}
vector<ll> costs(ll e)
{
	if(e == 0)
	{
		vector<ll> V(M + 1, 0);
		V[0] = 1;
		return V;
	}
	vector<ll> res = costs(e / 2);
	res = conv(res, res);
	if(e % 2) res = conv(res, base);
	return res;
}

int dp[22][MAX]; // [offset][matrix row | vector pos]

int main()
{
	cin >> M >> T >> P;
	for(int i = 0; i < (1 << M); i++) scanf("%d", E + i);
	base = vector<ll>(M + 1);
	for(int i = 0; i <= M; i++) cin >> base[i];

	vector<ll> matrix = costs(T);

	for(int o = 0; o <= M; o++) for(int i = 0; i < (1 << M); i++) dp[o][i] = (matrix[o] * E[i]) % P;
	for(int s = 1; s <= M; s++)
	{
		for(int o = 0; o <= M - s; o++)
			for(int p = 0; p < (1 << M); p += (1 << s))
				for(int r = 0; r < (1 << s); r++)
				{
					if(r < (1 << (s - 1))) dp[o][p + r] += dp[o + 1][p + r + (1 << (s - 1))];
					else dp[o][p + r] += dp[o + 1][p + r - (1 << (s - 1))];
					if(dp[o][p + r] >= P) dp[o][p + r] -= P;
				}
	}

	for(int i = 0; i < (1 << M); i++) printf("%d\n", dp[0][i]);
}
