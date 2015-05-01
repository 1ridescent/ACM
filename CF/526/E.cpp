#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, Q;
ll A[1000005];
ll sum = 0;
ll C;

int next[1000005];
int dp[1000005]; // min steps needed to go to [s, t]
int to[1000005]; // to what?

int go()
{
	if(C >= sum) return 1;
	int r = 0;
	ll cur = 0;
	for(int l = 0; l < N; )
	{
		while(cur + A[r] <= C)
		{
			cur += A[r];
			r++;
			if(r == N) r = 0;
			//cout << l << ' ' << r << ' ' << cur << endl;
		}
		next[l] = r;
		cur -= A[l];
		l++;
	}
	//for(int i = 0; i < N; i++) cout << next[i] << ' '; cout << endl;
	int s = 0, t = next[0];
	for(int i = N - 1; i >= 0; i--)
	{
		if(next[i] < i)
		{
			dp[i] = 1;
			to[i] = next[i];
		}
		else
		{
			dp[i] = 1 + dp[next[i]];
			to[i] = to[next[i]];
		}
	}
	int best = N;
	for(int i = s; i <= t; i++)
		best = min(best, dp[i] + (to[i] < i));
	return best;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> Q;
	for(int i = 0; i < N; i++)
	{
		cin >> A[i];
		sum += A[i];
	}
	while(Q--)
	{
		cin >> C;
		cout << go() << '\n';
	}
}
