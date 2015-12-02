#include <bits/stdc++.h>
using namespace std;

char B[55][55];
int cnt[256];
int ans;
int main()
{
	int R, C;
	cin >> R >> C;
	for(int i = 0; i < R; i++)
		for(int j = 0; j < C; j++)
			cin >> B[i][j];
	for(int r = 1; r < R; r++)
		for(int c = 1; c < C; c++)
		{
			memset(cnt, 0, sizeof(cnt));
			for(int i = -1; i <= 0; i++)
				for(int j = -1; j <= 0; j++)
					cnt[B[r + i][c + j]]++;
			if(cnt['f'] && cnt['a'] && cnt['c'] && cnt['e']) ans++;
		}
	cout << ans;
}
