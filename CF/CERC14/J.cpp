#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstdlib>
#include <cstdio>

using namespace std;

const int inf = 1e9;

struct edge
{
	int u, v, w;
};
bool cmp(edge a, edge b)
{
	return a.w < b.w;
}

int N, M;
edge E[100005];

int P[1005], W[1005], I[1005];
bool vis[1005];

inline int lca(int u, int v)
{
	memset(vis, 0, sizeof(vis));
	for(int x = u; x != 0; x = P[x])
		vis[x] = true;
	int x = v;
	while(x != 0 && !vis[x])
		x = P[x];
	return x;
}
void reroot(int r)
{
	//cout << "P[]: "; for(int ii = 1; ii <= N; ii++) cout << P[ii]; cout << endl;
	//cout << "I[]: "; for(int ii = 1; ii <= N; ii++) cout << I[ii]; cout << endl;
	//printf("rerooting %d\n", r);
	int u = r, v = P[r];
	int tu = u, tw = W[u], ti = I[u];
	P[r] = W[r] = I[r] = 0;
	while(v != 0)
	{
		u = v;
		v = P[v];
		int w0 = W[u], i0 = I[u];
		P[u] = tu, W[u] = tw, I[u] = ti;
		tu = u, tw = w0, ti = i0;
	}
	//cout << "P[]: "; for(int ii = 1; ii <= N; ii++) cout << P[ii]; cout << endl;
	//cout << "I[]: "; for(int ii = 1; ii <= N; ii++) cout << I[ii]; cout << endl;
}

int size[100005];
int ind[100005][1005];
#define SEG_SIZE 20
int seg[100005][1005 / SEG_SIZE + 2];
inline void add(int i, int ei)
{
	size[i]++;
	ind[i][size[i]] = ei;
	if(size[i] % SEG_SIZE == 0)
	{
		seg[i][size[i] / SEG_SIZE] = seg[i][size[i] / SEG_SIZE - 1];
		for(int j = -SEG_SIZE + 1; j <= 0; j++)
			seg[i][size[i] / SEG_SIZE] += E[ind[i][size[i] + j]].w;
	}
	//res[i][size[i]] = res[i][size[i] - 1] + E[ei].w;
	//printf("%d -> %d = %d\n", i, ei, res[i][size[i]]);
}

//bool used[100005];
map<int, int> low, high;

int main2()
{
	cin >> N >> M;
	for(int i = 1; i <= M; i++)
	{
		size[i] = 0;
		seg[i][0] = 0;
		cin >> E[i].u >> E[i].v >> E[i].w;
		if(rand() % 2) swap(E[i].u, E[i].v);
	}

	sort(E + 1, E + 1 + M, cmp);

	low.clear();
	for(int i = M; i >= 1; i--)
		low[E[i].w] = i;
	high.clear();
	for(int i = 1; i <= M; i++)
		high[E[i].w] = i;

	memset(P, 0, sizeof(P));
	memset(W, 0, sizeof(W));
	for(int i = 1; i <= M; i++)
	{
		int u = E[i].u, v = E[i].v, w = E[i].w;
		//printf("%d: edge (%d, %d, %d)\n", i, u, v, w);
		int l = lca(u, v);
		int s = 1;
		//printf("%d: lca(%d, %d) = %d\n", i, u, v, l);
		if(l != 0)
		{
			int min_i = inf, min_v = -1;
			for(int x = u; x != l; x = P[x])
				if(I[x] < min_i)
					min_i = I[x], min_v = x;
			for(int x = v; x != l; x = P[x])
				if(I[x] < min_i)
					min_i = I[x], min_v = x;
			//printf("min_v = %d\n", min_v);

			s = min_i;
			//printf("s = %d\n", s);
			//used[s] = false;
			s++;
			P[min_v] = 0, I[min_v] = 0, W[min_v] = 0;
		}
		//cout << "P[]: "; for(int ii = 1; ii <= N; ii++) cout << P[ii]; cout << endl;
		reroot(u);
		//cout << "P[]: "; for(int ii = 1; ii <= N; ii++) cout << P[ii]; cout << endl;
		P[u] = v;
		I[u] = i;
		W[u] = w;
		//used[i] = true;
		//cout << "P[]: "; for(int ii = 1; ii <= N; ii++) cout << P[ii]; cout << endl;
		//cout << "I[]: "; for(int ii = 1; ii <= N; ii++) cout << I[ii]; cout << endl;
		//cout << "used[]: "; for(int ii = 1; ii <= M; ii++) cout << used[ii]; cout << endl;

		for(int j = i; j >= s; j--)
		{
			add(j, i);
		}
	}

	int Q;
	cin >> Q;
	int c = 0;
	while(Q--)
	{
		int L, H;
		cin >> L >> H;
		L -= c, H -= c;
		map<int, int>::iterator it = low.lower_bound(L);
		if(it == low.end())
			c = 0;
		else
		{
			map<int, int>::iterator it2 = high.upper_bound(H);
			if(it2 == high.begin())
				c = 0;
			else
			{
				int l = it->second, h = (--it2)->second;
				//printf("l = %d, h = %d\n", l, h);
				/*int lo = 1, hi = size[l] + 1;
				while(lo + 1 < hi)
				{
					int mid = (lo + hi) / 2;
					if(ind[l][mid] <= h) lo = mid;
					else hi = mid;
				}
				c = res[l][lo];*/
				int s = 0;
				while((s + 1) * SEG_SIZE <= size[l] && ind[l][(s + 1) * SEG_SIZE] <= h)
					s++;
				int i = s * SEG_SIZE;
				c = seg[l][s];
				while(i + 1 <= size[l] && ind[l][i + 1] <= h)
				{
					i++;
					c += E[ind[l][i]].w;
				}
				//printf("i = %d\n", i);
			}
		}
		cout << c << '\n';
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) main2();
}
