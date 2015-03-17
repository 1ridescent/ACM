#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> seg;
#define l first
#define r second
#define inf 10000000

int N, M, D;
seg L[3005], R[3005];
map<int, int> nextL, nextR;
map<int, vector<int> > dp;


int main2()
{
	nextL.clear();
	nextR.clear();
	dp.clear();
	cin >> N >> M >> D;
	for(int i = 0; i < N; i++)
	{
		cin >> L[i].l >> L[i].r;
		nextL[L[i].l] = max(nextL[L[i].l], L[i].r);
		dp[L[i].r] = vector<int>(3005, inf);
	}
	for(int i = 0; i < M; i++)
	{
		cin >> R[i].l >> R[i].r;
		nextR[R[i].l] = max(nextR[R[i].l], R[i].r);
		dp[R[i].r] = vector<int>(3005, inf);
	}
	int m = 0;
	for(map<int, int>::iterator it = nextL.begin(); it != nextL.end(); it++)
	{
		m = max(it->second, m);
		it->second = m;
		//printf("L %d %d\n", it->first, m);
	}
	m = 0;
	for(map<int, int>::iterator it = nextR.begin(); it != nextR.end(); it++)
	{
		m = max(it->second, m);
		it->second = m;
		//printf("R %d %d\n", it->first, m);
	}

	dp[0] = vector<int>(3005, inf);
	dp[0][0] = 0;
	int ans = inf;
	for(map<int, vector<int> >::iterator it = dp.begin(); it != dp.end(); it++)
	{
		int l = it->first + D - 1;
		vector<int>& V = it->second;
		int m = inf;
		for(int i = 0; i <= 3003; i++)
		{
			m = min(V[i], m);
			V[i] = m;
		}
		if(l >= 80000000)
		{
			for(int i = 0; i <= 3003; i++)
				if(V[i] != -1)
					ans = min(ans, max(i, V[i]));
		}
		for(int i = 0; i < 3003; i++)
		{
			int j = V[i];
			if(j == inf) continue;
			map<int, int>::iterator it2 = nextL.upper_bound(l);
			if(it2 != nextL.begin())
			{
				it2--;
				int r = it2->second;
				if(r > it->first)
				{
					dp[r][i + 1] = min(dp[r][i + 1], j);
					//printf("L %d %d %d\n", r, i + 1, dp[r][i + 1]);
				}
			}
			it2 = nextR.upper_bound(l);
			if(it2 != nextR.begin())
			{
				it2--;
				int r = it2->second;
				if(r > it->first)
				{
					dp[r][i] = min(dp[r][i], j + 1);
					//printf("R %d %d %d\n", r, i, dp[r][i]);
				}
			}
		}
	}
	if(ans == inf) cout << "Lunchtime\n";
	else cout << ans << endl;
}

int main()
{
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++)
	{
		printf("Case #%d: ", i);
		main2();
	}
}
