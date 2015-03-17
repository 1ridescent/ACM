#include <bits/stdc++.h>

using namespace std;

const int inf = 11111;

int table[1005];
void build_table(string W)
{
	int pos = 2, cnd = 0;
	table[0] = -1, table[1] = 0;
	while(pos < W.size())
	{
		if(W[pos - 1] == W[cnd])
			cnd++, table[pos] = cnd, pos++;
		else if(cnd > 0)
			cnd = table[cnd];
		else
			table[pos] = 0, pos++;
	}
}

string T, W;
int dp[10005][1005]; // min remove

int main()
{
	cin >> T >> W;
	build_table(W);
	for(int i = 0; i < 10005; i++) for(int j = 0; j < 1005; j++) dp[i][j] = inf;
	dp[0][0] = 0;
	for(int i = 0; i < T.size(); i++)
	{
		for(int j = 0; j < W.size(); j++)
		{
			//printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
			// remove next
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
			// keep
			int j2 = j;
			while(j2 != -1 && W[j2] != T[i]) j2 = table[j2];
			if(j2 + 1 == W.size()) continue; // can't
			dp[i + 1][j2 + 1] = min(dp[i + 1][j2 + 1], dp[i][j]);
		}
	}
	int best = inf;
	for(int i = 0; i < W.size(); i++) best = min(best, dp[T.size()][i]);
	cout << best << endl;
}
