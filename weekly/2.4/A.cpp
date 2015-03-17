#include <bits/stdc++.h>

using namespace std;

int N;
int A[105][105];
int D[105][105];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= i; j++)
			cin >> A[i][j];
	D[1][1] = A[1][1];
	for(int i = 2; i <= N; i++)
	{
		for(int j = 1; j < i; j++) D[i][j] = max(D[i][j], A[i][j] + D[i - 1][j]);
		for(int j = 2; j <= i; j++) D[i][j] = max(D[i][j], A[i][j] + D[i - 1][j - 1]);
	}
	int ans = 0;
	for(int i = 1; i <= N; i++) ans = max(ans, D[N][i]);
	cout << ans << endl;
}
