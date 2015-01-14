#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;
const ll mod = 1000000;

int N, M;
char B[105][105];

int sr, sc;
char sd;
int tr, tc;

bool vis[105][105][93];
int dist[105][105][91];
ll num[105][105][93];
queue<int> Q;
inline void insert(int r, int c, char d, int l, ll n)
{
	if(B[r][c] == '*') return;
	if(vis[r][c][d])
	{
		if(l < dist[r][c][d])
		{
			dist[r][c][d] = l;
			num[r][c][d] = n;
		}
		else if(l == dist[r][c][d])
		{
			num[r][c][d] += n;
			num[r][c][d] %= mod;
		}
	}
	else
	{
		vis[r][c][d] = true;
		dist[r][c][d] = l;
		num[r][c][d] = n;
		Q.push(r); Q.push(c); Q.push(d);
	}
}
void bfs()
{
	memset(vis, 0, sizeof(vis));
	while(!Q.empty()) Q.pop();
	memset(num, 0, sizeof(num));

	insert(sr, sc, sd, 0, 1);
	while(!Q.empty())
	{
		int r = Q.front(); Q.pop();
		int c = Q.front(); Q.pop();
		char d = Q.front(); Q.pop();
		int l = dist[r][c][d];
		ll n = num[r][c][d];
		//printf("%d %d %c %d %d\n", r, c, d, l, (int)n);
		if(d == 'N')
		{
			insert(r, c, 'E', l + 1, n);
			insert(r, c, 'W', l + 1, n);
			for(r--; B[r][c] != '*'; r--) insert(r, c, 'N', l + 1, n);
		}
		if(d == 'E')
		{
			insert(r, c, 'N', l + 1, n);
			insert(r, c, 'S', l + 1, n);
			for(c++; B[r][c] != '*'; c++) insert(r, c, 'E', l + 1, n);
		}
		if(d == 'S')
		{
			insert(r, c, 'E', l + 1, n);
			insert(r, c, 'W', l + 1, n);
			for(r++; B[r][c] != '*'; r++) insert(r, c, 'S', l + 1, n);
		}
		if(d == 'W')
		{
			insert(r, c, 'N', l + 1, n);
			insert(r, c, 'S', l + 1, n);
			for(c--; B[r][c] != '*'; c--) insert(r, c, 'W', l + 1, n);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	while(true)
	{
		cin >> N >> M;
		if(!N && !M) break;
		memset(B, '*', sizeof(B));
		for(int r = 1; r <= N; r++)
			for(int c = 1; c <= M; c++)
			{
				cin >> B[r][c];
				char k = B[r][c];
				if(k == 'X') tr = r, tc = c;
				else if(k == 'N' || k == 'E' || k == 'S' || k == 'W')
				{
					sr = r, sc = c;
					sd = k;
				}
			}
		bfs();
		if(!vis[tr][tc]['N'])
		{
			cout << "0 0\n";
		}
		else
		{
			int len = dist[tr][tc]['N'];
			len = min(len, dist[tr][tc]['S']);
			len = min(len, dist[tr][tc]['E']);
			len = min(len, dist[tr][tc]['W']);
			ll res = 0;
			if(dist[tr][tc]['N'] == len) res += num[tr][tc]['N'];
			if(dist[tr][tc]['E'] == len) res += num[tr][tc]['E'];
			if(dist[tr][tc]['S'] == len) res += num[tr][tc]['S'];
			if(dist[tr][tc]['W'] == len) res += num[tr][tc]['W'];
			cout << len << ' ' << res % mod << '\n';
		}
	}
}
