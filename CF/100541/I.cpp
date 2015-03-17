#include <bits/stdc++.h>

using namespace std;

bool B[1005][1005];

int reach[4][1005][1005];
int dir[4][2] = { {0,-1}, {-1,0}, {1,0}, {0,1} };

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int N, M;
		scanf("%d %d", &N, &M);
		char input[1005];
		memset(B, 0, sizeof(B));
		for(int i = 1; i <= N; i++)
		{
			scanf("%s", input);
			for(int j = 1; j <= M; j++)
				B[i][j] = (input[j - 1] == '1');
		}
		memset(reach, 0, sizeof(reach));
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= M; j++)
				reach[0][i][j] = (B[i][j] ? reach[0][i - 1][j - 1] + 1 : 0);
		for(int i = 1; i <= N; i++)
			for(int j = M; j >= 1; j--)
				reach[1][i][j] = (B[i][j] ? reach[1][i - 1][j + 1] + 1 : 0);
		for(int i = N; i >= 1; i--)
			for(int j = 1; j <= M; j++)
				reach[2][i][j] = (B[i][j] ? reach[2][i + 1][j - 1] + 1 : 0);
		for(int i = N; i >= 1; i--)
			for(int j = M; j >= 1; j--)
				reach[3][i][j] = (B[i][j] ? reach[3][i + 1][j + 1] + 1 : 0);
		int res = 0;
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= M; j++)
			{
				int r = 0, a, b;
				for(int d = 0; d < 4; d++)
				{
					int a = reach[d][i][j], b = reach[d][i + dir[d][0]][j + dir[d][1]];
					if(a > b + 1) a = b + 1;
					if(b > a) b = a;
					r += a + b;
				}
				res = max(res, r);
			}
		cout << max(0, res - 3) << '\n';
	}
}
