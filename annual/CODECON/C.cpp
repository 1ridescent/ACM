#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int A[1005][1005];
int D[1005][1005];

int main()
{
	cin >> N >> M;
	for(int i = N; i >= 1; i--)
		for(int j = 1; j <= M; j++)
			cin >> A[i][j];
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			D[i][j] = max(D[i][j - 1], D[i - 1][j]) + A[i][j];
			//cout << i << ' ' << j << ' ' << D[i][j] << endl;
		}
	cout << D[N][M] << '\n';
}
