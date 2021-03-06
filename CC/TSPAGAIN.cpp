#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

int N, K;
int A[1005][1005];
int C[1005][1005];
int dpX[1005][1005], dpY[1005][1005];

int add(int x1, int y1, int x2, int y2)
{
	return C[min(x1, x2)][max(y1, y2)] - C[x1][y1] - C[x2][y2] + C[max(x1, x2)][min(y1, y2)];
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		memset(A, 0, sizeof(A));
		cin >> N >> K;
		while(K--)
		{
			int x, y;
			cin >> x >> y;
			x++, y++;
			A[x][y]++;
		}
		for(int x = 1000; x >= 1; x--)
			for(int y = 1; y <= 1000; y++)
				C[x][y] = A[x][y] + C[x + 1][y] + C[x][y - 1] - C[x + 1][y - 1];
		int res = 0;
		for(int i = 1; i <= N; i++) res += C[i][i];
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
				dpX[i][j] = dpY[i][j] = inf;
		dpX[1][1] = dpY[1][1] = 0;
		for(int i = 2; i <= N; i++)
		{
			for(int x = 1; x < i; x++) // (x, i - 1) and (i - 1, i - 2)
			{
				dpX[i][x] = min(dpX[i][x], dpX[i - 1][x] + add(x, i - 1, i, i));
				dpY[i][i - 2] = min(dpY[i][i - 2], dpX[i - 1][x] + add(i - 1, i - 2, i, i));
			}
			for(int y = 1; y < i; y++) // (i - 1, y) and (i - 2, i - 1)
			{
				dpY[i][y] = min(dpY[i][y], dpY[i - 1][y] + add(i - 1, y, i, i));
				dpX[i][i - 2] = min(dpX[i][i - 2], dpY[i - 1][y] + add(i - 2, i - 1, i, i));
			}
		}
		int best = inf;
		for(int i = 1; i <= N; i++)
			best = min(best, min(dpX[N][i], dpY[N][i]));
		cout << res + best << endl;
	}
}
