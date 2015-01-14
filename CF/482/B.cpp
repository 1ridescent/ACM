#include <iostream>
#include <cstring>

using namespace std;

int N, M;
int A[33][100005];
int Q[100005][3];
int R[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	memset(A, 0, sizeof(A));
	for(int m = 0; m < M; m++)
	{
		int l, r, q;
		cin >> l >> r >> q;
		Q[m][0] = l, Q[m][1] = r, Q[m][2] = q;
		for(int i = 0; i <= 30; i++)
			if(q & (1 << i))
				A[i][l]++, A[i][r + 1]--;
	}
	for(int i = 0; i <= 30; i++)
	{
		for(int j = 1; j <= N + 2; j++)
			A[i][j] += A[i][j - 1];
		for(int j = 1; j <= N; j++)
			A[i][j] = !!(A[i][j]);
	}
	memset(R, 0, sizeof(R));
	for(int j = 1; j <= N; j++)
		for(int i = 0; i <= 30; i++)
			R[j] += A[i][j] * (1 << i);
	for(int i = 0; i <= 30; i++)
	{
		for(int j = 1; j <= N; j++)
			A[i][j] += A[i][j - 1];
	}
	for(int m = 0; m < M; m++)
	{
		int l = Q[m][0], r = Q[m][1], q = Q[m][2];
		for(int i = 0; i <= 30; i++)
			if(!(q & (1 << i)))
			{
				if(A[i][r] - A[i][l - 1] == r - (l - 1))
				{
					cout << "NO\n";
					return 0;
				}
			}
	}
	cout << "YES\n";
	for(int i = 1; i <= N; i++) cout << R[i] << ' ';
}
