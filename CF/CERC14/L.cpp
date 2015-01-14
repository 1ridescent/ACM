#include <iostream>
#include <map>

using namespace std;

const int inf = 1e9;

int N;
int A[305], B[305], D[305];
int dp[605][605];

int main2()
{
	cin >> N;
	map<int, int> X;
	for(int i = 1; i <= N; i++)
	{
		cin >> A[i] >> B[i] >> D[i];
		X[A[i]] = X[B[i]] = -1;
	}

	int id = 0;
	for(map<int, int>::iterator it = X.begin(); it != X.end(); it++)
		it->second = ++id;
	for(int i = 1; i <= N; i++)
		A[i] = X[A[i]], B[i] = X[B[i]];
	int M = id;

	for(int l = 0; l <= M; l++)
		for(int s = 1; s <= M - l + 1; s++)
		{
			int t = s + l - 1;
			// find farthest
			int farthest = -1, farthest_i = -1;
			for(int i = 1; i <= N; i++)
			{
				if(!(s <= A[i] && B[i] <= t)) continue;
				if(D[i] > farthest)
					farthest = D[i], farthest_i = i;
			}
			if(farthest == -1)
			{
				dp[s][t] = 0;
				continue;
			}

			dp[s][t] = inf;
			for(int m = A[farthest_i]; m <= B[farthest_i]; m++)
			{
				dp[s][t] = min(dp[s][t], farthest + dp[s][m - 1] + dp[m + 1][t]);
			}
		}

	cout << dp[1][M] << '\n';
}

int main()
{
	int T;
	cin >> T;
	while(T--) main2();
}
