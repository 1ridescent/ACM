#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

string S, P;

int next[2020];
vector<int> Left[2020];

int dp[2020][2020];

int main()
{
	cin >> S >> P;
	for(int i = 0; i < S.size(); i++)
	{
		next[i] = -1;
		int p = 0;
		for(int j = i; j < S.size(); j++)
		{
			if(S[j] == P[p]) p++;
			if(p == P.size())
			{
				next[i] = j + 1;
				Left[j + 1].push_back(i);
				break;
			}
		}
		//cout << i << ' ' << next[i] << endl;
	}
/*
	memset(dp, 127, sizeof(dp));
	dp[0][0] = 0;
	for(int r = 1; r <= S.size(); r++)
	{
		for(int s = 0; s <= S.size(); s++)
		{
			dp[r][s] = min(dp[r][s], dp[r - 1][s]);
			for(int i = 0; i < Left[r].size(); i++)
			{
				int l = Left[r][i];
				dp[r][s + 1] = min(dp[r][s + 1], dp[l][s] + (r - l - (int)P.size()));
			}
		}
	}*/

	memset(dp, 128, sizeof(dp));
	dp[0][0] = 0;
	for(int r = 1; r <= S.size(); r++)
	{
		for(int d = 0; d <= S.size(); d++)
		{
			dp[r][d] = max(dp[r][d], dp[r - 1][d]);
			dp[r][d] = max(dp[r][d], dp[r - 1][d - 1]);
			for(int i = 0; i < Left[r].size(); i++)
			{
				int l = Left[r][i];
				int x = r - l - P.size();
				dp[r][d + x] = max(dp[r][d + x], dp[l][d] + 1);
			}
		}
	}

	for(int s = 0; s <= S.size(); s++)
		cout << dp[S.size()][s] << ' ';
}
