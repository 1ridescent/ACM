#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>

using namespace std;

int N, L;
vector< pair<int, int> > times[22];
int next[22][333333];

map<int, int> id;

int dp[1 << 20]; // max time after watching bitmasked movies

int main()
{
	freopen("movie.in", "r", stdin);	freopen("movie.out", "w", stdout);
	cin >> N >> L;
	id[0] = id[L] = -1;
	for(int i = 0; i < N; i++)
	{
		int C, l;
		cin >> l >> C;
		while(C--)
		{
			int s;
			cin >> s;
			times[i].push_back(make_pair(s, s + l));
			id[s] = id[s + l] = -1;
		}
	}
	int nextid = 0;
	for(map<int, int>::iterator it = id.begin(); it != id.end(); it++)
		it->second = ++nextid;
	int start = id[0], stop = id[L];
	memset(next, -1, sizeof(next));
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < times[i].size(); j++)
		{
			times[i][j].first = id[times[i][j].first];
			times[i][j].second = id[min(times[i][j].second, L)];
			//printf("%d %d: %d-%d\n", i, j, times[i][j].first, times[i][j].second);
			next[i][times[i][j].first] = times[i][j].second;
		}
		for(int t = start + 1; t <= stop; t++)
			if(next[i][t - 1] >= t)
				next[i][t] = max(next[i][t], next[i][t - 1]);
	}
	memset(dp, -1, sizeof(dp));
	dp[0] = start;
	int ans = 123;
	for(int b = 0; b < (1 << N); b++)
	{
		if(dp[b] >= stop)
			ans = min(ans, __builtin_popcount(b));
		for(int i = 0; i < N; i++)
		{
			int b2 = (b | (1 << i));
			if(b == b2) continue;
			dp[b2] = max(dp[b2], next[i][dp[b]]);
		}
	}
	cout << (ans == 123 ? -1 : ans);
}
