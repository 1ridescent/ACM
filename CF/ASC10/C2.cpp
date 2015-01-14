#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long ll;
const ll INF = 1e17;

int N;
ll A[2020];
ll cumul[2020];

ll dp[2020][2020];
int numleft[2020][2020];

inline ll sum(int l, int r);
inline ll calc_split(int l, int r, int n);
inline ll calc(int l, int r);

inline ll sum(int l, int r)
{
	return cumul[r] - cumul[l - 1];
}
inline ll calc_split(int l, int r, int n)
{
	return calc(l, l + n - 1) + calc(l + n, r) + sum(l, r);
}
inline ll calc(int l, int r)
{
	if(l > r) return 0;
	if(l == r)
	{
		numleft[l][r] = 0;
		dp[l][r] = 0;
		return dp[l][r];
	}
	if(l + 1 == r)
	{
		numleft[l][r] = 1;
		dp[l][r] = A[l] + A[r];
		//cout << l << ' ' << r << ": " << dp[l][r] << endl;
		return dp[l][r];
	}
	if(dp[l][r] != INF) return dp[l][r];

	calc(l, r - 1);
	calc(l + 1, r);
	int numleft_l = numleft[l][r - 1], numleft_r = 1 + numleft[l + 1][r];
	/*int numleft_l = 1, numleft_r = r - l;

	while(numleft_r - numleft_l > 10) // L..1..2..R
	{
		int numleft1 = (numleft_l * 2 + numleft_r) / 3;
		int numleft2 = (numleft_l + numleft_r * 2) / 3;
		if(calc_split(l, r, numleft1) < calc_split(l, r, numleft2)) numleft_r = numleft2;
		else numleft_l = numleft1;
	}*/
	for(int n = numleft_l; n <= numleft_r; n++)
	{
		if(calc_split(l, r, n) < dp[l][r])
		{
			dp[l][r] = calc_split(l, r, n);
			numleft[l][r] = n;
		}
	}
	//cout << l << ' ' << r << ": " << dp[l][r] << endl;
	return dp[l][r];
}
void print(int l, int r, string prefix)
{
	if(l == r)
	{
		cout << prefix << '\n';
		return;
	}
	/*if(l + 1 == r)
	{
		cout << prefix + '0' << '\n' << prefix + '1' << '\n';
		return;
	}*/
	int n = numleft[l][r];
	print(l, l + n - 1, prefix + '0');
	print(l + n, r, prefix + '1');
}

int main()
{
	freopen("codes.in", "r", stdin); freopen("codes.out", "w", stdout);
	for(int i = 0; i < 2020; i++) for(int j = 0; j < 2020; j++) dp[i][j] = INF;

	cin >> N;
	cumul[0] = 0;
	for(int i = 1; i <= N; i++)
	{
		cin >> A[i];
		cumul[i] = cumul[i - 1] + A[i];
	}
	calc(1, N);
	print(1, N, "");
	return 0;
}
