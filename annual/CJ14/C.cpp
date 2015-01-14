#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

struct point
{
	int x, y;
};
struct bdg
{
	point ll, ur;
};
int dist(bdg a, bdg b)
{
	int dx = min(abs(a.ll.x - b.ur.x), abs(a.ur.x - b.ll.x)) - 1;
	int dy = min(abs(a.ll.y - b.ur.y), abs(a.ur.y - b.ll.y)) - 1;
	//cout << "dx=" << dx << ", dy=" << dy << endl;
	if(!(a.ll.x > b.ur.x || b.ll.x > a.ur.x)) // overlap x
	{
		//cout << "overlap x\n";
		return dy;
	}
	if(!(a.ll.y > b.ur.y || b.ll.y > a.ur.y)) // overlap y
	{
		//cout << "overlap y\n";
		return dx;
	}
	return max(dx, dy);
}

bdg bdgs[1010];
int G[1010][1010];
int D[1010];
bool visited[1010];
int dijkstra(int N, int s, int t)
{
	memset(visited, 0, sizeof(visited));
	for(int i = 1; i <= N; i++) D[i] = 123123123;
	D[s] = 0;
	while(true)
	{
		int best = 123123123, besti;
		for(int i = 1; i <= N; i++)
			if(!visited[i] && D[i] < best)
				best = D[i], besti = i;
		if(besti == t) return best;
		visited[besti] = true;
		for(int i = 1; i <= N; i++)
			if(!visited[i])
				D[i] = min(D[i], D[besti] + G[besti][i]);
	}
}

int main2()
{
	int W, H, B;
	cin >> W >> H >> B;
	for(int i = 1; i <= B; i++)
	{
		cin >> bdgs[i].ll.x >> bdgs[i].ll.y >> bdgs[i].ur.x >> bdgs[i].ur.y;
	}
	bdgs[B + 1].ll.x = -1, bdgs[B + 1].ll.y = 0, bdgs[B + 1].ur.x = -1, bdgs[B + 1].ur.y = H - 1;
	bdgs[B + 2].ll.x = W, bdgs[B + 2].ll.y = 0, bdgs[B + 2].ur.x = W, bdgs[B + 2].ur.y = H - 1;
	for(int i = 1; i <= B + 2; i++)
		for(int j = 1; j <= B + 2; j++)
		{
			if(i != j)
			{
				//cout << i << ' ' << j << ' ' << dist(bdgs[i], bdgs[j]) << endl;
				G[i][j] = dist(bdgs[i], bdgs[j]);
			}
		}

	int N = B + 2;
	/*for(int k = 1; k <= N; k++)
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);*/
	cout << dijkstra(N, B + 1, B + 2) << endl;
}

int main()
{
	/*while(true)
	{
		bdg a, b;
		cin >> a.ll.x >> a.ll.y >> a.ur.x >> a.ur.y >> b.ll.x >> b.ll.y >> b.ur.x >> b.ur.y;
		cout << dist(a, b);
	}*/
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cout << "Case #" << t << ": ";
		main2();
	}
}
