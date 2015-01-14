#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ll;
const ll INF = (1LL << 55);

int N, M;
ll A[1010][1010];
ll dpAS[1010][1010], dpAT[1010][1010];
ll dpBS[1010][1010], dpBT[1010][1010];

int main()
{
	cin >> N >> M;
	for(int r = 1; r <= N; r++)
		for(int c = 1; c <= M; c++)
		{
			int x;
			scanf("%d", &x);
			A[r][c] = x;
		}

	for(int i = 0; i < 1010; i++)
		for(int j = 0; j < 1010; j++)
			dpAS[i][j] = dpAT[i][j] = dpBS[i][j] = dpBT[i][j] = -INF;

	dpAS[1][1] = A[1][1];
	for(int r = 1; r <= N; r++)
		for(int c = 1; c <= M; c++)
		{
			if(r == 1 && c == 1) continue;
			dpAS[r][c] = A[r][c] + max(dpAS[r - 1][c], dpAS[r][c - 1]);
		}
	dpAT[N][M] = A[N][M];
	for(int r = N; r >= 1; r--)
		for(int c = M; c >= 1; c--)
		{
			if(r == N && c == M) continue;
			dpAT[r][c] = A[r][c] + max(dpAT[r + 1][c], dpAT[r][c + 1]);
		}
	dpBS[N][1] = A[N][1];
	for(int r = N; r >= 1; r--)
		for(int c = 1; c <= M; c++)
		{
			if(r == N && c == 1) continue;
			dpBS[r][c] = A[r][c] + max(dpBS[r + 1][c], dpBS[r][c - 1]);
		}
	dpBT[1][M] = A[1][M];
	for(int r = 1; r <= N; r++)
		for(int c = M; c >= 1; c--)
		{
			if(r == 1 && c == M) continue;
			dpBT[r][c] = A[r][c] + max(dpBT[r - 1][c], dpBT[r][c + 1]);
		}

	ll best = -1;
	for(int r = 2; r <= N - 1; r++)
		for(int c = 2; c <= M - 1; c++)
		{
			best = max(best, max(dpAS[r][c - 1] + dpAT[r][c + 1] + dpBS[r + 1][c] + dpBT[r - 1][c],
								 dpAS[r - 1][c] + dpAT[r + 1][c] + dpBS[r][c - 1] + dpBT[r][c + 1]));
		}

	cout << best << endl;
}
