#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int N, M;
char A[105][105];

bool check(int r, int c, int s)
{
	if(r + s > N || c + s > M) return false;
	char t = A[r][c];
	for(int i = c; i < c + s; i++)
		if(A[r][i] != t) return false;
	for(int i = c; i < c + s; i++)
		if(A[r + s - 1][i] != t) return false;
	for(int i = r; i < r + s; i++)
		if(A[i][c] != t) return false;
	for(int i = r; i < r + s; i++)
		if(A[i][c + s - 1] != t) return false;
	return true;
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < N; i++)
	{
		string S;
		cin >> S;
		//cout << S << endl;
		for(int j = 0; j < M; j++)
			A[i][j] = S[j];

	}


	for(int s = min(N, M); s >= 2; s--)
	{
		for(int r = 0; r < N; r++)
			for(int c = 0; c < M; c++)
				if(check(r, c, s))
				{
					//cout << A[r][c] << endl;
					printf("%c\n%d,%d\n%d,%d", A[r][c], c, r, c + s - 1, r + s - 1);
					return 0;
				}
	}
}
