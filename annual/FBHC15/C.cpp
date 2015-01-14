#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
int type[256];

int R, C;
char B[105][105];

bool inside(int r, int c)
{
	return (1 <= r && r <= R && 1 <= c && c <= C);
}
bool ok(int r0, int c0, int t0)
{
	if(B[r0][c0] == '#') return false;
	for(int r = 1; r <= R; r++)
		for(int c = 1; c <= C; c++)
		{
			if(type[B[r][c]] != -1)
			{
				int r2 = r, c2 = c;
				while(B[r2][c2] != '#')
				{
					if(r2 == r0 && c2 == c0)
						return false;
					r2 += dir[(type[B[r][c]] + t0) % 4][0];
					c2 += dir[(type[B[r][c]] + t0) % 4][1];
				}
			}
		}
	return true;
}

bool vis[105][105][4];
queue<int> Q;

int main()
{
	memset(type, -1, sizeof(type));
	type['>'] = 0, type['v'] = 1, type['<'] = 2, type['^'] = 3;
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cin >> R >> C;
		int sr, sc, tr, tc;
		memset(B, '#', sizeof(B));
		for(int r = 1; r <= R; r++)
			for(int c = 1; c <= C; c++)
			{
				cin >> B[r][c];
				if(B[r][c] == 'S')
					sr = r, sc = c;
				if(B[r][c] == 'G')
					tr = r, tc = c;
			}

		while(!Q.empty()) Q.pop();
		memset(vis, 0, sizeof(vis));
		vis[sr][sc][0] = true;
		Q.push(sr); Q.push(sc); Q.push(0);
		int ans = -1;
		while(!Q.empty())
		{
			int r0 = Q.front(); Q.pop();
			int c0 = Q.front(); Q.pop();
			int t0 = Q.front(); Q.pop();
			if(r0 == tr && c0 == tc)
			{
				ans = t0;
				break;
			}
			for(int d = 0; d < 4; d++)
			{
				int r1 = r0 + dir[d][0], c1 = c0 + dir[d][1];
				int t1 = t0 + 1;
				if(!vis[r1][c1][t0 % 4] && ok(r1, c1, t1))
				{
					vis[r1][c1][t0 % 4] = true;
					Q.push(r1); Q.push(c1); Q.push(t1);
				}
			}
		}

		cout << "Case #" << t << ": ";
		if(ans == -1) cout << "impossible\n";
		else cout << ans << '\n';
	}
}
