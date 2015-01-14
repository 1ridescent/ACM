#include <iostream>
#include <algorithm>

using namespace std;

int N, K;
int A[44];
int P[44];
int seg[44][44]; // [i][n]: at most n from [1,i]
int dp[44][1604][44];

int main()
{
	cin >> N >> K;
	for(int i = 1; i <= N; i++) cin >> P[i];
	for(int i = 1; i <= N; i++) cin >> A[i];
	A[0] = 0;
	for(int i = 0; i <= N; i++)
		for(int n = 0; n <= 40; n++)
		{
			seg[i][n] = 0;
			for(int k = 1; k <= i; k++) seg[i][n] += min(n, A[k]) * P[k];
		}
	for(int i = 0; i < 44; i++) for(int k = 0; k < 1604; k++) for(int n = 0; n < 44; n++) dp[i][k][n] = 0;
	for(int i = N; i >= 1; i--)
		for(int k = 0; k <= 1600; k++)
			for(int n = 0; n <= 40; n++)
			{
				for(int b = 0; b <= A[i]; b++) // bought this many i
				{
					if(n - b >= 0 && k - b * P[i] >= 0)
					{
						int add = seg[i][n] - seg[i][n - b];
						//if(n > A[i]) add -= P[i] * (n - A[i]);
						dp[i][k][n] = max(dp[i][k][n], dp[i + 1][k - b * P[i]][n - b] + add);
					}
				}
				//if(k <= 30 && n <= 10) cout << i << ' ' << k << ' ' << n << ' ' << dp[i][k][n] << endl;
			}
	int best = 0;
	for(int i = 0; i <= 40; i++) best = max(best, dp[1][min(K, 1600)][i]);
	cout << best << endl;
	return 0;
}
