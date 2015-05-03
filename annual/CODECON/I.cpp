#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int N;
map<int, int> Xid, Yid;
int data[100005][5];
int cnt[1005][1005];
bool vis[1005][1005];
int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

#define LIM 1005

void flood(int x, int y)
{
	//printf("%d %d\n", x, y);
	if(x < 0 || x == LIM) return;
	if(y < 0 || y == LIM) return;
	vis[x][y] = true;
	for(int i = 0; i < 4; i++)
	{
		int dx = dir[i][0], dy = dir[i][1];
		if(!vis[x + dx][y + dy] && !cnt[x + dx][y + dy]) flood(x + dx, y + dy);
	}
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int n, t, l, r, b;
		cin >> n >> t >> l >> r >> b;
		data[i][0] = n;
		data[i][1] = t;
		data[i][2] = l;
		data[i][3] = r;
		data[i][4] = b;
		Xid[l] = Xid[r] = -1;
		Yid[t] = Yid[b] = -1;
	}
	int nextid = 0;
	for(map<int, int>::iterator it = Xid.begin(); it != Xid.end(); it++)
		it->second = ++nextid;
	nextid = 0;
	for(map<int, int>::iterator it = Yid.begin(); it != Yid.end(); it++)
		it->second = ++nextid;
	for(int i = 0; i < N; i++)
	{
		int n = data[i][0];
		int t = Yid[data[i][1]];
		int l = Xid[data[i][2]];
		int r = Xid[data[i][3]];
		int b = Yid[data[i][4]];
		//printf("%d -> %d\n",data[i][4],b);
		//printf("%d %d %d %d %d\n",n,t,l,r,b);
		for(int x = l; x < r; x++)
			for(int y = b; y < t; y++)
			{
				//printf("%d: %d %d += %d\n",i,x,y,n);
				cnt[x][y] += n;
			}
	}
	int best = 0;
	int comp = 0;
	for(int i = 1; i < LIM; i++)
	{
		for(int j = 1; j < LIM; j++)
		{
			//printf("%d ", cnt[i][j]);
			best = max(best, cnt[i][j]);
			if(!vis[i][j] && !cnt[i][j])
			{
				flood(i, j);
				comp++;
			}
		}
		//cout << endl;
	}
	cout << best << ' ' << comp << endl;
}
