#include <iostream>
#include <complex>
#include <queue>
#include<cstdio>
using namespace std;

typedef complex<int> point;
#define X real()
#define Y imag()

const complex<int> ray = complex<int>(31, 37);

int cross(point u, point v)
{
	return u.X*v.Y - u.Y*v.X;
}
bool intersects(point a, point b, point t)
{
	bool res = ((cross(a-t, ray) < 0) ^ (cross(b-t, ray) < 0));
	//if(res) printf("(%d,%d) (%d,%d)\n",a.X,a.Y,b.X,b.Y);
	if(a.X == b.X) res &= (a.X > t.X);
	else res &= (a.Y > t.Y);
	return res;
}

int N, M;
char board[22][22];

point S;
struct treasure
{
	int id;
	int val;
	point loc;
};
vector<treasure> T;
vector<point> B;
point start;

int val[13];

int shortest[22][22][277];
queue<int> Q;

int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int main()
{
	cin >> N >> M;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
		{
			cin >> board[i][j];
			if('0' <= board[i][j] && board[i][j] <= '9')
			{
				treasure t;
				t.id = board[i][j] - '0';
				t.loc = point(i, j);
				T.push_back(t);
			}
			if(board[i][j] == 'B')
			{
				B.push_back(point(i, j));
			}
			if(board[i][j] == 'S')
			{
				start = point(i, j);
				board[i][j] = '.';
			}
		}
	for(int i = 0; i < 22; i++)
		for(int j = 0; j < 22; j++)
			for(int b = 0; b < 257; b++)
				shortest[i][j][b] = 1231231231;
	shortest[start.X][start.Y][0] = 0;
	Q.push(start.X);
	Q.push(start.Y);
	Q.push(0);
	Q.push(0);
	while(!Q.empty())
	{
		int r = Q.front();
		Q.pop();
		int c = Q.front();
		Q.pop();
		int mask = Q.front();
		Q.pop();
		int dist = Q.front()+1;
		Q.pop();
		//printf("%d %d %x %d\n",r,c,mask,dist-1);
		for(int d = 0; d < 4; d++)
		{
			int r2 = r + dir[d][0], c2 = c + dir[d][1];
			int mask2 = mask;
			if(r2 < 0 || r2 >= N || c2 < 0 || c2 >= M
					|| board[r2][c2] != '.') continue;
			for(int t = 0; t < T.size(); t++)
			{
				if(intersects(point(r,c),point(r2,c2),T[t].loc)) mask2 ^= (1<<t);
			}
			for(int b = 0; b < B.size(); b++)
			{
				if(intersects(point(r,c),point(r2,c2),B[b])) mask2 ^= (1<<(T.size()+b));
			}
			if(dist < shortest[r2][c2][mask2])
			{
				shortest[r2][c2][mask2] = dist;
				Q.push(r2);
				Q.push(c2);
				Q.push(mask2);
				Q.push(dist);
			}
		}
	}
	for(int i = 1; i <= T.size(); i++)
	{
		cin >> val[i];
	}
	int best = 0;
	for(int mask = 0; mask < (1<<T.size()); mask++)
	{
		int total = -shortest[start.X][start.Y][mask];
		for(int t = 0; t < T.size(); t++)
		{
			if(mask & (1<<t))
			{
				total += val[T[t].id];
			}
		}
		best = max(best, total);
	}
	cout << best << endl;
	return 0;
}
