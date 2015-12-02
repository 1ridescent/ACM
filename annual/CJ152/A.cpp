#include <bits/stdc++.h>

using namespace std;

pair<int, int> dir[256];

int R, C;
char B[105][105];
pair<int, int> to[105][105];

bool inside(int r, int c)
{
	return (1 <= r && r <= R && 1 <= c && c <= C);
}

pair<int, int> nxt(int r, int c, pair<int, int> d)
{
	int dr = d.first, dc = d.second;
	while(true)
	{
		r += dr;
		c += dc;
		if(!inside(r, c)) return make_pair(-1, -1);
		if(B[r][c] != '.') return make_pair(r, c);
	}
}
bool can(int r, int c)
{
	if(nxt(r, c, dir['^']).first != -1) return true;
	if(nxt(r, c, dir['>']).first != -1) return true;
	if(nxt(r, c, dir['v']).first != -1) return true;
	if(nxt(r, c, dir['<']).first != -1) return true;
	return false;
}

bool vis[105][105];
bool cycle[105][105];
int num_out;
pair<int, int> dfs(int r, int c)
{
	vis[r][c] = true;
	int tr = to[r][c].first, tc = to[r][c].second;
	if(tr == -1)
	{
		num_out++;
		return make_pair(-1, -1);
	}
	else if(vis[tr][tc]) return make_pair(tr, tc);

	pair<int, int> p = dfs(tr, tc);
	if(p.first != -1) cycle[r][c] = true;
	if(p.first == r && p.second == c) return make_pair(-1, -1);
	else return p;
}

int main2()
{
	cin >> R >> C;
	for(int r = 1; r <= R; r++)
		for(int c = 1; c <= C; c++)
			cin >> B[r][c];
	for(int r = 1; r <= R; r++)
		for(int c = 1; c <= C; c++)
			if(B[r][c] != '.')
			{
				if(!can(r, c))
				{
					printf("IMPOSSIBLE\n");
					return 0;
				}
				to[r][c] = nxt(r, c, dir[B[r][c]]);
			}
	memset(vis, 0, sizeof(vis));
	memset(cycle, 0, sizeof(cycle));
	num_out = 0;
	for(int r = 1; r <= R; r++)
		for(int c = 1; c <= C; c++)
			if(B[r][c] != '.' && !vis[r][c])
				dfs(r, c);
	int ans = 0;
	for(int r = 1; r <= R; r++)
		for(int c = 1; c <= C; c++)
			if(B[r][c] != '.' && !cycle[r][c])
				ans++;
	cout << num_out << endl;
}

int main()
{
	dir['^'] = make_pair(-1, 0);
	dir['<'] = make_pair(0, -1);
	dir['v'] = make_pair(1, 0);
	dir['>'] = make_pair(0, 1);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		printf("Case #%d: ", t);
		main2();
	}
}
