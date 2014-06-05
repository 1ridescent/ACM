#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

int N, M;
char board[111][111];
char board2[111][111];
bool cleared[111][111];

void clear(int n, int m, int b)
{
	if(cleared[n][m]) return;
	cleared[n][m] = true;
	for(int i = n; i < n+b && i < N; i++)
		for(int j = m; j < m+b && j < M; j++)
		{
			if(j > m && board2[i][j-1] != 'X' && board2[i][j] == 'X') break;
			board2[i][j] = 'X';
		}
}

int hist[111][111];
bool test(int B)
{
	//cout << "B = " << B << endl;
	for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) cleared[i][j] = false;
	memcpy(board2, board, sizeof(board));
	for(int t = 0; t < (N-B+1)*(M-B+1); t++)
	{
		for(int i = 0; i < N; i++)
		{
			int cnt = 0;
			for(int j = M-1; j >= 0; j--)
			{
				cnt = ((board2[i][j] != 'S') ? (cnt+1) : 0);
				hist[i][j] = cnt;
			}
		}
		//for(int i = 0; i < N; i++) { for(int j = 0; j < M; j++) cout << board2[i][j]; cout << endl; } cout << endl;
		//for(int i = 0; i < N; i++) { for(int j = 0; j < M; j++) cout << hist[i][j] << ' '; cout << endl; } cout << endl;
		for(int j = 0; j < M; j++)
		{
			int cnt = 0;
			for(int i = N-1; i >= 0; i--)
			{
				cnt = ((hist[i][j] >= B) ? (cnt+1) : 0);
				if(cnt >= B) clear(i, j, B);
			}
		}
		for(int i = 0; i < N; i++)
		{
			int cnt = 0;
			for(int j = M-1; j >= 0; j--)
			{
				cnt = (board2[i][j] != 'R' ? cnt+1 : 0);
				hist[i][j] = cnt;
			}
		}
		for(int j = 0; j < M; j++)
		{
			int cnt = 0;
			for(int i = N-1; i >= 0; i--)
			{
				cnt = (hist[i][j] >= B ? cnt+1 : 0);
				if(cnt >= B) clear(i, j, B);
			}
		}
		bool good = true;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				if(board2[i][j] != 'X')
					good = false;
		if(good) return true;
	}
	return false;
}

int main()
{
	freopen("skicourse.in", "r", stdin); freopen("skicourse.out", "w", stdout);
	cin >> N >> M;
	for(int i = 0; i < N; i++) for(int j = 0; j < M; j++) cin >> board[i][j];
	int low = 0, high = min(N, M)+1;
	while(low + 1 < high)
	{
		int mid = (low+high)/2;
		if(test(mid)) low = mid;
		else high = mid;
	}
	cout << low << endl;
	return 0;
}
