#include <iostream>
#include <cstring>

using namespace std;

const int LGMAX = 18;
const int MAX = (1 << LGMAX);
const int INF = 100000000;

int N, M;
char maze[3][200200];
int path[LGMAX][MAX][2][2];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int r = 1; r <= 2; r++) for(int c = 1; c <= N; c++) cin >> maze[r][c];

	memset(path, 32, sizeof(path));
	for(int i = 1; i <= N - 1; i++)
	{
		if(maze[1][i] == '.' && maze[1][i + 1] == '.') path[0][i][1][1] = 1;
		if(maze[2][i] == '.' && maze[2][i + 1] == '.') path[0][i][2][2] = 1;
		if(maze[1][i] == '.' && maze[2][i + 1] == '.' && (maze[1][i + 1] == '.' || maze[2][i] == '.')) path[0][i][1][2] = 2;
		if(maze[2][i] == '.' && maze[1][i + 1] == '.' && (maze[1][i] == '.' || maze[2][i + 1] == '.')) path[0][i][2][1] = 2;
	}
	for(int b = 1; b < LGMAX; b++)
	{
		for(int h = 1; h <= N - (1 << b); h++)
		{
			int dp[3][3][3]; // [][i][j] : from i to j
			memset(dp, 32, sizeof(dp));
			for(int s = 1; s <= 2; s++) dp[0][s][s] = 0;
			for(int t = 1; t <= 2; t++)
			{
				for(int s = 1; s <= 2; s++)
				{
					for(int i = 1; i <= 2; i++)
						for(int j = 1; j <= 2; j++)
						{
							dp[t][s][j] = min(dp[t][s][j], dp[t - 1][s][i] + path[b - 1][h + (t - 1) * (1 << (b - 1))][i][j]);
						}
				}
			}
			for(int i = 1; i <= 2; i++)
			    for(int j = 1; j <= 2; j++)
			    {
			        path[b][h][i][j] = dp[2][i][j];
			    }
		}
	}
	for(int m = 0; m < M; m++)
	{
	    pair<int, int> S, T;
	    cin >> S.second >> T.second;
	    if(S.second <= N) S.first = 1;
	    else S.first = 2, S.second -= N;
	    if(T.second <= N) T.first = 1;
	    else T.first = 2, T.second -= N;
	    if(S.second == T.second)
	    {
	        cout << (S.first != T.first) << '\n';
	        continue;
	    }
	    
	    if(S.second > T.second) swap(S, T);
	    int dist = T.second - S.second;
	    int dp[LGMAX + 5][3][3];
	    memset(dp, 32, sizeof(dp));
		for(int s = 1; s <= 2; s++) dp[0][s][s] = 0;
		int t = 0;
	    for(int b = LGMAX; b >= 0; b--)
	    {
	        if((1 << b) <= dist)
	        {
	            t++;
	            for(int s = 1; s <= 2; s++)
				{
					for(int i = 1; i <= 2; i++)
						for(int j = 1; j <= 2; j++)
						{
							dp[t][s][j] = min(dp[t][s][j], dp[t - 1][s][i] + path[b][S.second][i][j]);
						}
				}
				S.second += (1 << b);
				dist -= (1 << b);
	        }
	    }
	    cout << (dp[t][S.first][T.first] > INF ? -1 : dp[t][S.first][T.first]) << '\n';
	}
}
