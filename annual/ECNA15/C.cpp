#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> cell;
#define r first
#define c second

int N, M;
ll T;
char op;
cell C[11];

ll ans = 0;

int cur_r[11], cur_c[11];
void dfs_plus(int i, int s)
{
//	printf("%d %d\n", i, s);
	if(i == M - 1)
	{
		int rem = T - s;
//		printf("rem = %d, r = %d c = %d\n",rem,cur_r[C[i].r],cur_c[C[i].c]);
		if((1 <= rem && rem <= N) && !((cur_r[C[i].r] | cur_c[C[i].c]) & (1 << rem)))
			ans++;
		return;
	}
	for(int n = 1; n <= N; n++)
	{
		int b = (1 << n);
		int& r = cur_r[C[i].r];
		int& c = cur_c[C[i].c];
		if((r | c) & b) continue;
		r ^= b;
		c ^= b;
		dfs_plus(i + 1, s + n);
		r ^= b;
		c ^= b;
	}
}

void dfs_mult(int i, ll s)
{
	if(i == M - 1)
	{
		ll rem = T / s;
		if((1 <= rem && rem <= N) && !((cur_r[C[i].r] | cur_c[C[i].c]) & (1 << rem)))
			ans++;
		return;
	}
	for(int n = 1; n <= N; n++)
	{
		int b = (1 << n);
		int& r = cur_r[C[i].r];
		int& c = cur_c[C[i].c];
		if((r | c) & b) continue;
		if(T % (s * n)) continue;
		r ^= b;
		c ^= b;
		dfs_mult(i + 1, s * n);
		r ^= b;
		c ^= b;
	}
}

int main()
{
	cin >> N >> M >> T >> op;
	for(int i = 0; i < M; i++) cin >> C[i].r >> C[i].c;
	sort(C, C + M);
	if(op == '+') dfs_plus(0, 0);
	else if(op == '*') dfs_mult(0, 1);
	else if(M == 2)
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
			{
				if(j == i) continue;
				if(op == '-' && abs(i - j) == T) ans++;
				if(op == '/' && (i == T * j || j == T * i)) ans++;
			}
	cout << ans << endl;
}
