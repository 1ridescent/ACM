#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

int N;
int dp[22][52][52][28];
int seg[22][52][52]; // -1 if anything, -2 if bad
int num[22][52][52];

int len[52];
int dict[52][22];

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		string s;
		cin >> s;
		len[i] = s.size();
		for(int j = 0; j < s.size(); j++)
		{
			dict[i][j] = (s[j] - 'a' + 1);
			if(s[j] == '?') dict[i][j] = -1;
		}
	}
	for(int i = 0; i < 20; i++)
		for(int start = 0; start < N; start++)
			for(int end = start; end < N; end++)
			{
				int res = -1;
				for(int j = start; j <= end; j++)
				{
					if(dict[j][i] == -1)
					{
						num[i][start][end]++;
						continue;
					}
					else if(res >= 0 && res != dict[j][i])
						res = -2;
					else if(res == -1)
						res = dict[j][i];
				}
				seg[i][start][end] = res;
				//printf("seg[%d][%d][%d] = %d\n",i,start,end,res);
			}
	for(int i = 0; i < N; i++)
		for(int c = 0; c <= 27; c++)
			dp[20][i][i][c] = 1;
	for(int i = 19; i >= 0; i--)
		for(int l = 1; l <= N; l++)
			for(int start = 0; start <= N - l; start++)
			{
				int end = start + l - 1;
				for(int c = 26; c >= 0; c--)
				{
					ll val = dp[i][start][end][c + 1]; // skip c
					for(int mid = start; mid <= end; mid++) // [start, mid] = c
					{
						if(c == 0 && (seg[i][start][mid] != 0 || num[i][start][mid])) continue;
						if(seg[i][start][mid] != -1 && seg[i][start][mid] != c) continue;
						ll add = dp[i + 1][start][mid][0];
						if(mid < end) add = (add * dp[i][mid + 1][end][c + 1]) % mod;
						val += add;
					}
					val %= mod;
					dp[i][start][end][c] = val;
					//printf("dp[%d][%d][%d][%d] = %d\n",i,start,end,c,dp[i][start][end][c]);
				}
			}
	cout << dp[0][0][N - 1][0] << endl;
}
