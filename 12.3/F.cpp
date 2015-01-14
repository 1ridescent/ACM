#include <iostream>
#include <cstdio>

using namespace std;

const int inf = 2010201020;

int N, M;
int A[55][55];

int partial[55][55];

int dp[55][55][55][55];

int main()
{
	cin >> N >> M;
	for(int r = 1; r <= N; r++)
		for(int c = 1; c <= M; c++)
			cin >> A[r][c];

	for(int r = 1; r <= N; r++)
	{
		partial[r][M + 1] = 0;
		for(int c = M; c >= 1; c--)
			partial[r][c] = partial[r][c + 1] + A[r][c];
	}

	for(int lr = 1; lr <= N; lr++)
		for(int lc = 1; lc <= M; lc++)
		{
			for(int sr = 1; sr <= N - lr + 1; sr++)
				for(int sc = 1; sc <= M - lc + 1; sc++)
				{
					if(lr == 1 && lc == 1)
					{
						dp[lr][lc][sr][sc] = 0;
						continue;
					}
					int num = 0;
					for(int r = sr; r < sr + lr; r++)
						num += partial[r][sc] - partial[r][sc + lc];
					int add = inf;
					for(int xr = 1; xr < lr; xr++)
						add = min(add, dp[xr][lc][sr][sc] + dp[lr - xr][lc][sr + xr][sc]);
					for(int xc = 1; xc < lc; xc++)
						add = min(add, dp[lr][xc][sr][sc] + dp[lr][lc - xc][sr][sc + xc]);

					dp[lr][lc][sr][sc] = num + add;
					//printf("%d %d %d %d: num=%d add=%d res=%d\n", lr, lc, sr, sc, num, add, num + add);
				}
		}

	cout << dp[N][M][1][1] << '\n';
}
