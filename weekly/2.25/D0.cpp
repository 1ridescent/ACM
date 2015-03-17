#include <bits/stdc++.h>

using namespace std;

int N, M;
pair<int, int> S[100005];
int maxL[100005];

int ans[100005];

int check()
{
	int res = 0;
	for(int i = 1; i <= N; i++)
	{
		//cout << ans[i] << (i == N ? '\n' : ' ');
		res += ans[i];
		ans[i] += ans[i - 1];
	}
	for(int i = 0; i < M; i++)
	{
		int l = S[i].first, r = S[i].second;
		if(ans[r] - ans[l - 1] != 1) return -1;
	}
	return res;
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int l, r;
		cin >> l >> r;
		S[i] = make_pair(l, r);
		maxL[r] = max(maxL[r], l);
	}
	for(int i = 2; i <= N; i++)
		maxL[i] = max(maxL[i], maxL[i - 1]);
	sort(S, S + M);
	int curL = 1;
	int m = 0;
	for(int i = 0; i < M; i++)
	{
		int l = S[i].first, r = S[i].second;
		//printf("seg [%d, %d]: curL = %d, m = %d\n", l, r, curL, m);
		while(curL < l)
			ans[curL++] = 1;
		if(curL > r) continue;
		if(m < l)
		{
			m = max(curL, maxL[r]);
			ans[m] = 1;
		}
		curL = r + 1;
	}
	while(curL <= N)
		ans[curL++] = 1;
	cout << check() << endl;
}
