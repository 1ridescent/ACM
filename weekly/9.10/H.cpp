#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

const int MAX = 1337;
const int INF = 123123123;

int H;
vector<int> G[MAX];
char B[MAX];
int id[100][100];
int loc[4];
int nextid = 0;

int dir[6][2] = { {0,1}, {0,-1}, {1,0}, {1,1}, {-1,0}, {-1,-1} };

int col(int r)
{
	return max(0, r - H);
}
int len(int r)
{
	return (2 * H - 1) - abs(H - r);
}
bool inside(int r, int c)
{
	return (1 <= r && r <= 2 * H - 1) && (col(r) <= c && c < col(r) + len(r));
}
bool letter(char k)
{
	return ('A' <= k && k <= 'D');
}

int dist[MAX][MAX];
priority_queue< pair<int, int> > Q;
void dijkstra(int s)
{
	for(int i = 0; i < nextid; i++) dist[s][i] = -1;
	Q.push(make_pair(-0, s));
	while(!Q.empty())
	{
		int u = Q.top().second;
		int d = -Q.top().first;
		Q.pop();
		if(dist[s][u] != -1) continue;
		dist[s][u] = d;
		//cout << s << " -> " << u << " : " << d << endl;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			int w = !(B[u] != '.' && B[u] == B[v]);
			//cout << u << ' ' << v << " : " << w << endl;
			Q.push(make_pair(-(d + w), v));
		}
	}
}

int main()
{
	while(true)
	{
		for(int i = 0; i < MAX; i++) G[i].clear();
		nextid = 0;
		memset(B, '.', sizeof(B));

		cin >> H;
		if(!H) return 0;
		for(int r = 1; r <= 2 * H - 1; r++)
		{
			for(int c = col(r); c < col(r) + len(r); c++)
			{
				id[r][c] = nextid++;
				char k;
				cin >> k;
				B[id[r][c]] = k;
				if(letter(k)) loc[k - 'A'] = id[r][c];
			}
		}

		for(int r = 1; r <= 2 * H - 1; r++)
		{
			for(int c = col(r); c < col(r) + len(r); c++)
			{
				for(int i = 0; i < 6; i++)
				{
					int r2 = r + dir[i][0];
					int c2 = c + dir[i][1];
					if(inside(r2, c2)) G[id[r][c]].push_back(id[r2][c2]);
				}
			}
		}

		for(int s = 0; s < nextid; s++) dijkstra(s);
		//for(int i = 0; i < nextid; i++) cout << B[i]; cout << endl;

		int best = INF;
		for(int s = 0; s < nextid; s++)
			for(int t = s; t < nextid; t++)
			{
				for(int b = 0; b < 16; b++)
				{
					int cur = -3 + dist[s][t];
					//if(B[s] == 'B' && B[t] == 'B')printf("%d %d:\n", s, t);
					for(int i = 0; i < 4; i++)
					{
						int u = ((b & (1 << i)) ? s : t);
						cur += dist[loc[i]][u];
					}
					if(cur < best)
					{
						best = cur;
						//printf("s=%d t=%d : %d\n", s, t, cur);
					}
				}
			}

		printf("You have to buy %d parcels.\n", best);
	}
}
