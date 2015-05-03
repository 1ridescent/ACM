#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

string board[4] = { "...","...","...","*.*" };
ll dp[13][4][3];
int dir[8][2] = { {1,2}, {1,-2}, {-1,2}, {-1,-2}, {2,1}, {2,-1}, {-2,1}, {-2,-1} };

int main()
{
	int N;
	cin >> N;
	dp[0][0][0] = 1;
	for(int s = 0; s < N; s++)
	{
		for(int r = 0; r < 4; r++)
			for(int c = 0; c < 3; c++)
			{
				for(int i = 0; i < 8; i++)
				{
					int dr = dir[i][0], dc = dir[i][1];
					int r2 = r + dr, c2 = c + dc;
					if(0 <= r2 && r2 < 4 && 0 <= c2 && c2 < 3 && board[r2][c2] == '.')
					{
						dp[s + 1][r2][c2] += dp[s][r][c];
					}
				}
			}
	}
	cout << dp[N][2][2] << endl;
	return 0;
}
