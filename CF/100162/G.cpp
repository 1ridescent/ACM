#include <bits/stdc++.h>

using namespace std;

int N, M, L, R;
int cnt = 0;

char cur[35];
void dfs(int l, int p)
{
	if(p == 0 || cur[0] > cur[p])
	{
		cnt++;
		if(L <= cnt && cnt <= R)
		{
			cur[l] = '\0';
			puts(cur);
		}
		if(cnt >= R) return;
	}
	if(l == N) return;
	cur[l] = cur[p];
	dfs(l + 1, p + 1);
	for(char c = cur[p] + 1; c < 'a' + M; c++)
	{
		cur[l] = c;
		dfs(l + 1, 0);
		if(cnt >= R)
	}
}

int main()
{
	int tests = 0;
	while(scanf("%d %d %d %d", &N, &M, &L, &R) == 4)
	{
		tests++;
		printf("Case %d:\n", tests);
		cnt = 0;
		for(char c = 'a'; c < 'a' + M; c++)
		{
			cur[0] = c;
			dfs(1, 0);
		}
	}
}
