#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int L, M;
int A[105];
int T[30][30];

pair<string, int> dp[105][30];

inline char alpha(int i)
{
	return (char)('a' + i - 1);
}

int main()
{
	freopen("ssh.in", "r", stdin); freopen("ssh.out", "w", stdout);

	cin >> L >> M;
	for(int i = 1; i < L; i++) cin >> A[i];
	for(int r = 1; r <= M; r++) for(int c = 1; c <= M; c++) cin >> T[r][c];

	for(int m = 1; m <= M; m++)
	{
		string s = ".";
		s[0] = alpha(m);
		dp[0][m] = make_pair(s, 0);
	}
	for(int i = 1; i < L; i++)
	{
		for(int m1 = 1; m1 <= M; m1++)
		{
			for(int m2 = 1; m2 <= M; m2++)
			{
				pair<string, int> val = make_pair( dp[i - 1][m1].first + alpha(m2), dp[i - 1][m1].second + abs(A[i] - T[m1][m2]) );
				if(dp[i][m2].first == "" || val.second < dp[i][m2].second)
					dp[i][m2] = val;
			}
		}
	}
	pair<string, int> best;
	for(int m = 1; m <= M; m++)
	{
		if(best.first == "" || dp[L - 1][m].second < best.second) best = dp[L - 1][m];
	}
	cout << best.first << endl;
	return 0;
}
