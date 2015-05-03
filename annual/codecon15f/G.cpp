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

int dir[8][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };

int H, W, N;
char B[210][210];

int vis[210][210];
void flood(int r, int c, int m, char b)
{
	vis[r][c] = m;
	for(int i = 0; i < 8; i++)
	{
		int r2 = r + dir[i][0];
		int c2 = c + dir[i][1];
		if(!vis[r2][c2] && B[r2][c2] == b)
			flood(r2, c2, m, b);
	}
}

int res[234234];

int main()
{
	cin >> H >> W >> N;
	memset(B, 'x', sizeof(B));
	for(int i = 1; i <= 207; i++)
		for(int j = 1; j <= 207; j++)
			B[i][j] = '.';
	for(int i = 0; i < N; i++)
	{
		int r, c;
		cin >> r >> c;
		r += 4, c += 4;
		B[r][c] = '*';
	}
	flood(1, 1, -1, '.');
	vector<int> sizes;
	int next_id = 1;
	for(int i = 1; i <= 207; i++)
		for(int j = 1; j <= 207; j++)
		{
			if(!vis[i][j] && B[i][j] == '*')
			{
				int cnt = 0;
				flood(i, j, next_id, '*');
				sizes.push_back(next_id);
				next_id++;
			}
		}
	for(int r = 1; r <= 207; r++)
		for(int c = 1; c <= 207; c++)
			if(B[r][c] == '*')
				for(int i = 0; i < 8; i++)
				{
					int r2 = r + dir[i][0];
					int c2 = c + dir[i][1];
					if(!vis[r2][c2])
					{
						int s = vis[r][c];
						flood(r2, c2, next_id, '.');
						res[s]++;
						next_id++;
					}
				}
	for(int i = 0; i < sizes.size(); i++)
		sizes[i] = res[sizes[i]];
	sort(sizes.begin(), sizes.end());
	if(sizes.empty())
	{
		cout << "No colonies\n";
		return 0;
	}
	for(int i = 0; i < sizes.size(); i++)
	{
		cout << sizes[i];
		cout << (i < sizes.size() - 1 ? ' ' : '\n');
	}
	return 0;
}
