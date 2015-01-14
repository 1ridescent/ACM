#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int A[1616][1616];
vector<int> G[1616];

int R[1616];
void init()
{
	for(int i = 0; i < 1616; i++) R[i] = i;
}
int find(int u)
{
	if(R[u] == u) return u;
	R[u] = find(R[u]);
	return R[u];
}
void uni(int u, int v)
{
	R[find(u)] = find(v);
}

struct edge
{
	int u, v, w;
};
bool cmp_edge(edge a, edge b)
{
	return a.w < b.w;
}
vector<edge> V;

int index(int r, int c)
{
	return r * M + c;
}

int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

int main()
{
	cin >> M >> N;
	for(int r = 0; r < N; r++)
		for(int c = 0; c < M; c++)
			cin >> A[r][c];

	for(int r = 0; r < N; r++)
		for(int c = 0; c < M; c++)
		{
			for(int d = 0; d < 4; d++)
			{
				int dr = dir[d][0], dc = dir[d][1];
				int r2 = r + dr, c2 = c + dc;
				if(0 <= r2 && r2 < N && 0 <= c2 && c2 < M)
				{
					edge e;
					e.u = index(r, c);
					e.v = index(r2, c2);
					e.w = min(A[r][c], A[r2][c2]);
					V.push_back(e);
				}
			}
		}

	sort(V.begin(), V.end(), cmp_edge);

	init();
	int res = 0;
	for(int i = 0; i < V.size(); i++)
	{
		edge e = V[i];
		if(find(e.u) == find(e.v)) continue;
		res += e.w;
		uni(e.u, e.v);
	}

	cout << res << endl;
}
