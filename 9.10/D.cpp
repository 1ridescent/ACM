#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

int R, C;
char B[105][105];
bool vis[105][105][16];
int sr, sc;
int tr, tc;

bool is_key(char c)
{
	return ('a' <= c && c <= 'z');
}
bool is_door(char c)
{
	return ('A' <= c && c <= 'Z');
}
char charmap[256];

int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

queue<int> Q; // row, col, dist, keys
int main2()
{
	charmap['b'] = charmap['B'] = 0;
	charmap['y'] = charmap['Y'] = 1;
	charmap['r'] = charmap['R'] = 2;
	charmap['g'] = charmap['G'] = 3;

	while(!Q.empty()) Q.pop();
	memset(vis, 0, sizeof(vis));

	vis[sr][sc][0] = true;
	Q.push(sr); Q.push(sc); Q.push(0); Q.push(0);
	while(!Q.empty())
	{
		int r = Q.front(); Q.pop();
		int c = Q.front(); Q.pop();
		int d = Q.front(); Q.pop();
		int k = Q.front(); Q.pop();
		//printf("%d %d %d\n", r, c, d);
		for(int i = 0; i < 4; i++)
		{
			int dr = dir[i][0], dc = dir[i][1];
			//printf("%d %d\n", dr, dc);
			int r2 = r + dr, c2 = c + dc;
			int d2 = d + 1;
			char b = B[r2][c2];

			//printf("try %d %d %d : %c\n", r2, c2, d2, b);

			if(b == '#') continue;
			if(b == 'X')
			{
				printf("Escape possible in %d steps.\n", d2);
				return 0;
			}

			int k2 = k;
			if(is_key(b)) k2 |= (1 << (charmap[b]));
			if(is_door(b) && !( k2 & (1 << (charmap[b])) )) continue;

			if(vis[r2][c2][k2]) continue;
			vis[r2][c2][k2] = true;
			Q.push(r2); Q.push(c2); Q.push(d2); Q.push(k2);
		}
	}
	printf("The poor student is trapped!\n");
}

int main()
{
while(true) {
	memset(B, '#', sizeof(B));
	cin >> R >> C;
	if(R == 0 && C == 0) return 0;
	for(int r = 1; r <= R; r++)
		for(int c = 1; c <= C; c++)
		{
			cin >> B[r][c];
			if(B[r][c] == '*') sr = r, sc = c;
			if(B[r][c] == 'X') tr = r, tc = c;
		}

	main2();
}
}
