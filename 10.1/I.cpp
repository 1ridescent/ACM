#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

typedef long long ll;

ll num[40040];
ll sum[40040];
ll expect[40040];

int R, C;
char B[205][205];
int sr, sc, tr, tc;
int dir[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

int dist[205][205];
queue<pair<int, int> > Q;
const int inf = 40000;
void bfs()
{
	for(int r = 0; r < 205; r++)
		for(int c = 0; c < 205; c++)
			dist[r][c] = inf;
	dist[tr][tc] = 0;
	Q.push(make_pair(tr, tc));
	while(!Q.empty())
	{
		int r = Q.front().first, c = Q.front().second;
		int d = dist[r][c];
		Q.pop();
		for(int i = 0; i < 4; i++)
		{
			int dr = dir[i][0], dc = dir[i][1];
			int r2 = r + dr, c2 = c + dc;
			if(B[r2][c2] != 'X' && dist[r2][c2] == inf)
			{
				dist[r2][c2] = d + 1;
				Q.push(make_pair(r2, c2));
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cout << setprecision(3) << fixed;
	while(true)
	{
		cin >> R >> C;
		if(!R && !C) break;

		int num0 = 0;
		memset(B, 'X', sizeof(B));
		for(int r = 1; r <= R; r++)
			for(int c = 1; c <= C; c++)
			{
				cin >> B[r][c];
				if(B[r][c] == 'Y')
					sr = r, sc = c;
				else if(B[r][c] == 'E')
					tr = r, tc = c;
				if(B[r][c] != 'X') num0++;
			}

		bfs();
		/*for(int r = 1; r <= R; r++)
			for(int c = 1; c <= C; c++)
				cout << dist[r][c] << ' ';
		cout << endl;*/

		memset(num, 0, sizeof(num));
		for(int r = 1; r <= R; r++)
			for(int c = 1; c <= C; c++)
			{
				if(B[r][c] != 'X') num[dist[r][c]]++;
			}

		for(int i = 0; i <= 10; i++) cout << num[i] << ' '; cout << endl;
		sum[0] = num[0];
		for(int i = 1; i <= 40000; i++)
		{
			sum[i] = sum[i - 1] + num[i];
		}
		expect[0] = 0 * num[0];
		for(int i = 1; i <= 40000; i++)
		{
			expect[i] = expect[i - 1] + i * num[i];
		}

		//cout << sr << ' ' << sc << ' ' << dist[sr][sc] << endl;
		double best = dist[sr][sc];
		for(int thr = 0; thr < dist[sr][sc]; thr++)
		{
			double prob = sum[thr] * 1.0 / num0;
			double total = 1 / prob + expect[thr] * 1.0 / sum[thr];
			//cout << thr << " : " << prob << ' ' << total << endl;
			best = min(best, total);
		}
		cout << best << '\n';
	}
}
