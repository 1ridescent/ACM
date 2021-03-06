#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 2e18;

int N;
ll K;
int A[100005];
int substr(int s, int l)
{
	int r = 0;
	for(int i = 0; i < l; i++)
	{
		r *= 5;
		r += A[s + i];
	}
	return r;
}
set<int> subs[13];
int best[5][5];


map<ll, ll> dp[5][5];
ll compute(ll x, int a, int b)
{
	if(x < best[a][b]) return 0;
	if(x == 1) return 1;
	if(dp[a][b].count(x)) return dp[a][b][x];
	//cout << "at " << x << endl;
	ll r = 1;
	for(ll m = x / 2; m <= min(x / 2 + 11, x - 1); m++)
		for(int c = 0; c < 4; c++)
			r = max(r, compute(m, a, c) + compute(x - m, c, b));
	dp[a][b][x] = r;
	return r;
}

int main()
{
	cin >> K;
	string S;
	cin >> S;
	N = S.size();
	for(int i = 1; i <= N; i++)
		A[i] = (S[i - 1] - 'A');
	for(int len = 1; len <= 11; len++)
	{
		for(int s = 1; s <= N - len + 1; s++)
			subs[len].insert(substr(s, len));
	}
	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 5; j++)
			best[i][j] = (j == 4 ? 1 : 13);
	for(int len = 1; len <= 10; len++)
	{
		for(int t = 0; t < 4; t++)
			for(int s = 1; s <= N - len + 1; s++)
				if(!subs[len + 1].count(substr(s, len) * 5 + t))
				{
					best[A[s]][t] = min(best[A[s]][t], len);
					for(int t2 = 0; t2 < 5; t2++)
						best[A[s]][t2] = min(best[A[s]][t2], len + 1);
				}
	}
	//for(int i = 0; i < 4; i++) { for(int j = 0; j < 5; j++) cout << best[i][j] << ' '; cout << endl; }
	ll ans = 1;
	for(int s = 0; s < 4; s++)
		ans = max(ans, compute(K, s, 4));
	cout << ans << endl;
}
