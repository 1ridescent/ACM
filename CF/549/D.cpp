#include <bits/stdc++.h>

using namespace std;

int R, C, ans;
int B[105][105];

void paint(int r, int c, int d)
{
	for(int i = 1; i <= r; i++)
		for(int j = 1; j <= c; j++)
			B[i][j] += d;
}

int main()
{
	cin >> R >> C;
	for(int r = 1; r <= R; r++)
		for(int c = 1; c <= C; c++)
		{
			char ch;
			cin >> ch;
			if(ch == 'W') B[r][c] = 1;
			else B[r][c] = -1;
		}
	for(int r = R; r >= 1; r--)
		for(int c = C; c >= 1; c--)
		{
			if(B[r][c] != 0)
			{
				ans++;
				paint(r, c, -B[r][c]);
			}
		}
	cout << ans;
}
