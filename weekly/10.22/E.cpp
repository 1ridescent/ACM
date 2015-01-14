#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int K, W, H;
char board[1005][1005];
int cost[256];
int sr, sc;

int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

bool vis[1005][1005];
int dist[1005][1005];
priority_queue<pair<int, pair<int, int> > > Q;
int dijkstra()
{
	memset(vis, 0, sizeof(vis));
	Q.push(make_pair(-0, make_pair(sr, sc)));
	//cout << sr << ' ' << sc << endl;
	while(!Q.empty())
	{
		int d = -Q.top().first;
		int r = Q.top().second.first, c = Q.top().second.second;
		//cout << r << ' ' << c << ' ' << H << ' ' << W << endl;
		Q.pop();
		if(vis[r][c]) continue;
		vis[r][c] = true;
		dist[r][c] = d;
		for(int i = 0; i < 4; i++)
		{
			int dr = dir[i][0], dc = dir[i][1];
			int r2 = r + dr, c2 = c + dc;
			//cout << r2 << ' ' << c2 << endl;
			if(1 <= r2 && r2 <= H && 1 <= c2 && c2 <= W)
			{
				Q.push(make_pair(-(d + cost[board[r2][c2]]), make_pair(r2, c2)));
			}
		}
	}
	/*for(int i = 1; i <= H; i++)
	{
		for(int j = 1; j <= W; j++)
			cout << dist[i][j] << ' ';
		cout << endl;
	}*/
	int best = dist[1][1];
	for(int r = 1; r <= H; r++)
		for(int c = 1; c <= W; c++)
			if(r == 1 || r == H || c == 1 || c == W)
				best = min(best, dist[r][c]);
	return best;
}

int main()
{
	//ios::sync_with_stdio(false);
	//cin.tie(0);
	int T;
	cin >> T;
	while(T--)
	{
		cin >> K >> W >> H;
		for(int i = 0; i < K; i++)
		{
			char k;
			cin >> k;
			cin >> cost[k];
		}
		for(int i = 1; i <= H; i++)
		{
			scanf("%s", &board[i][1]);
			for(int j = 1; j <= W; j++)
			{
				//cin >> board[i][j];
				if(board[i][j] == 'E')
					sr = i, sc = j;
			}
		}

		cout << dijkstra() << '\n';
	}
}
