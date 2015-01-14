#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

#define DEBUG 0

int N, M;
char B[707][707];
bool vis[707][707];
int dist[707][707];
int dist2[707][707];

int dir[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

pair<int, int> you, vik, tre;
queue<int> Q;
int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	memset(B, 'I', sizeof(B));
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			cin >> B[i][j];
			if(B[i][j] == 'Y') you = make_pair(i, j);
			if(B[i][j] == 'V') vik = make_pair(i, j);
			if(B[i][j] == 'T') tre = make_pair(i, j);
		}

	memset(vis, 0, sizeof(vis));
	Q.push(vik.first); Q.push(vik.second); Q.push(0);
	while(!Q.empty())
	{
		int r = Q.front(); Q.pop();
		int c = Q.front(); Q.pop();
		int d = Q.front(); Q.pop();
		if(vis[r][c]) continue;
		if(DEBUG) cout << r << ' ' << c << ' '<<d<<endl;
		vis[r][c] = true;
		dist[r][c] = d;
		for(int i = 0; i < 4; i++)
		{
			int dr = dir[i][0], dc = dir[i][1];
			int r2 = r + dr, c2 = c + dc;
			if(B[r2][c2] != 'I')
			{
				Q.push(r2); Q.push(c2); Q.push(d + 1);
			}
		}
	}

	if(DEBUG) {for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= M; j++) cout << dist[i][j] << ' ';
		cout << endl;
	}}

	for(int r = 1; r <= N; r++)
		for(int c = 1; c <= M; c++)
			dist2[r][c] = 123123123;
	vector<int> seg;
	for(int r = 0; r <= N + 1; r++)
	{
		for(int c = 0; c <= M + 1; c++)
		{
			if(B[r][c] == 'I')
			{
				int low = 123123123;
				for(int i = 0; i < seg.size(); i++)
				{
					low = min(low, dist[r][seg[i]]);
				}
				for(int i = 0; i < seg.size(); i++)
				{
					dist2[r][seg[i]] = min(dist2[r][seg[i]], low);
				}
				seg.clear();
			}
			else seg.push_back(c);
		}
	}
	for(int c = 0; c <= M + 1; c++)
	{
		for(int r = 0; r <= N + 1; r++)
		{
			if(B[r][c] == 'I')
			{
				int low = 123123123;
				for(int i = 0; i < seg.size(); i++)
				{
					low = min(low, dist[seg[i]][c]);
				}
				for(int i = 0; i < seg.size(); i++)
				{
					dist2[seg[i]][c] = min(dist2[seg[i]][c], low);
				}
				seg.clear();
			}
			else seg.push_back(r);
		}
	}

	if(DEBUG){for(int i = 1; i <= N; i++)
		{
			for(int j = 1; j <= M; j++) cout << dist2[i][j] << ' ';
			cout << endl;
		}}

	memset(dist, 0, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	Q.push(you.first); Q.push(you.second); Q.push(0);
	while(!Q.empty())
	{
		int r = Q.front(); Q.pop();
		int c = Q.front(); Q.pop();
		int d = Q.front(); Q.pop();
		if(vis[r][c]) continue;
		vis[r][c] = true;
		dist[r][c] = d;
		if(r == tre.first && c == tre.second)
		{
			cout << "YES\n";
			return 0;
		}
		for(int i = 0; i < 4; i++)
		{
			int dr = dir[i][0], dc = dir[i][1];
			int r2 = r + dr, c2 = c + dc;
			if(B[r2][c2] != 'I' && d + 1 < dist2[r2][c2])
			{
				Q.push(r2); Q.push(c2); Q.push(d + 1);
			}
		}
	}
	cout << "NO\n";
	return 0;
}
