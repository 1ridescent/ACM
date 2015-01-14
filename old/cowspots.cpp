#include <iostream>
#include <queue>

using namespace std;

const int INF = (1 << 20);

int R, C;
int grid[55][55];

typedef pair<int, int> cell;
queue< pair<cell, int> > Q;
#define r first
#define c second
int dist[5][55][55];
void bfs(int k)
{
	for(int t = 0; t < 111; t++)
	{
		for(int r = 0; r < R; r++) for(int c = 0; c < C; c++)
		{
			if(r > 0) dist[k][r][c] = min(dist[k][r][c], dist[k][r-1][c]+1);
			if(r < R-1) dist[k][r][c] = min(dist[k][r][c], dist[k][r+1][c]+1);
			if(c > 0) dist[k][r][c] = min(dist[k][r][c], dist[k][r][c-1]+1);
			if(c < C-1) dist[k][r][c] = min(dist[k][r][c], dist[k][r][c+1]+1);
		}
	}
	/*while(!Q.empty())
	{
		cell c = Q.front().first;
		cout << Q.size() <<' ' << c.r << ' ' << c.c<< endl;
		int d = Q.front().second;
		Q.pop();
		dist[k][c.r][c.c] = d;
		if(c.r < R-1 && d+1 < dist[k][c.r+1][c.c]) Q.push( make_pair( cell(c.r+1, c.c), d+1));
		if(c.r > 0 && d+1 < dist[k][c.r-1][c.c]) Q.push( make_pair( cell(c.r-1, c.c), d+1));
		if(c.c < C-1 && d+1 < dist[k][c.r][c.c+1]) Q.push( make_pair( cell(c.r, c.c+1), d+1));
		if(c.c > 0 && d+1 < dist[k][c.r][c.c-1]) Q.push( make_pair( cell(c.r, c.c-1), d+1));
	}*/
	//cout << "DONE\n";
}
void flood_fill(int r, int c, int x)
{
	if(grid[r][c] != -1) return;
	grid[r][c] = x;
	if(r < R-1) flood_fill(r+1, c, x);
	if(r > 0) flood_fill(r-1, c, x);
	if(c < C-1) flood_fill(r, c+1, x);
	if(c > 0) flood_fill(r, c-1, x);
}

int spotdist[4][4];

int main()
{
	cin >> R >> C;
	for(int i = 0; i < R; i++) for(int j = 0; j < C; j++)
	{
		char c;
		cin >> c;
		grid[i][j] = (c == '.' ? 0 : -1);
	}
	int x = 0;
	for(int i = 0; i < R; i++) for(int j = 0; j < C; j++)
	{
		if(grid[i][j] == -1)
		{
			++x;
			//cout << x << endl;
			flood_fill(i, j, x);
			for(int i = 0; i < 55; i++) for(int j = 0; j < 55; j++) dist[x][i][j] = INF;
			for(int r = 0; r < R; r++) for(int c = 0; c < C; c++)
			{
				if(grid[r][c] == x)
				{
					dist[x][r][c] = 0;
					//Q.push( make_pair( cell(r, c), 0) );
				}
			}
			bfs(x);
		}
	}
	for(int i = 1; i <= 3; i++) for(int j = 1; j <= 3; j++)
	{
		spotdist[i][j] = INF;
		for(int r = 0; r < R; r++) for(int c = 0; c < C; c++)
		{
			if(grid[r][c] == j) spotdist[i][j] = min(spotdist[i][j], dist[i][r][c]);
		}
	}
	int bestdist = INF;
	for(int i = 1; i <= 3; i++)
	{
		int tempdist = 0;
		for(int j = 1; j <= 3; j++)
			if(j != i) tempdist += spotdist[i][j] - 1;
		bestdist = min(bestdist, tempdist);
	}
	for(int r = 0; r < R; r++) for(int c = 0; c < C; c++)
	{
		bestdist = min(bestdist,  (dist[1][r][c]-1) + (dist[2][r][c]-1) + (dist[3][r][c]-1) + 1 );
	}
	cout << bestdist << endl;
	return 0;
}
