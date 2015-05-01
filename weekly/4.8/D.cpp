#include <bits/stdc++.h>

using namespace std;

int N, M;
int B[256][256];

int pref[3][256][256];

void get_pref(int c0, int c1)
{
	for(int t = 0; t <= 2; t++)
		for(int j = c0; j <= c1; j++)
			for(int i = N; i >= 1; i--)
				pref[t][i][j] = pref[t][i + 1][j] + (B[i][j] == t);
}
int filled = 0;
int len;
void stamp(int r, int c)
{
	//printf("stamping %d %d\n", r, c);
	for(int i = r; i < r + len; i++)
		for(int j = c; j < c + len; j++)
			if(B[i][j] != 2)
			{
				B[i][j] = 2;
				filled++;
			}
	if(filled == N * M)
	{
		cout << len << endl;
		exit(0);
	}
	get_pref(c, c + len - 1);
}

void output()
{
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++) cout << B[i][j] << ' ';
		cout << endl;
	}
}

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			char c;
			cin >> c;
			B[i][j] = (c == 'R');
		}
	len = min(N, M);
	get_pref(1, M);
	while(true)
	{
		//printf("len = %d\n", len);
		//output();
		int cnt[3];
		bool done = false;
		for(int i = 1; i <= N; i++)
		{
			cnt[0] = cnt[1] = cnt[2] = 0;
			for(int j = 1; j <= M; j++)
			{
				cnt[2] = (pref[2][i][j] - pref[2][i + len][j] == len ? cnt[2] + 1 : 0);
				for(int t = 0; t <= 1; t++)
				{
					cnt[t] = ((pref[t][i][j] - pref[t][i + len][j]) + (pref[2][i][j] - pref[2][i + len][j]) == len ? cnt[t] + 1 : 0);
					//printf("%d %d %d %d %d\n", i, j, t, cnt[t], cnt[2]);
					if(cnt[t] >= len && cnt[2] < len) // fill
					{
						//printf("passed\n");
						stamp(i, j - len + 1);
						done = true;
					}
				}
			}
		}
		if(!done) len--;
		assert(len > 0);
	}
}
