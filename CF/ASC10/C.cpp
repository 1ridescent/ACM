#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstdlib>

using namespace std;

typedef long long ll;

#define left 0
#define right 1

int N;
vector<int> G[4020];
int P[4020];
int root;

ll val[4020];
ll total[4020];
ll w_total[4020];

void fix(int v, int d)
{
	if(G[v].empty())
	{
		//cout << v << ' ' << val[v] << endl;
		total[v] = val[v];
		w_total[v] = d * val[v];
	}
	else
	{
		total[v] = w_total[v] = 0;
		for(int i = 0; i < G[v].size(); i++)
		{
			int w = G[v][i];
			fix(w, d + 1);
			total[v] += total[w];
			w_total[v] += w_total[w];
		}
	}
}
void rotate_left(int s)
{
	int t = G[s][right];
	int a = G[s][left], b = G[t][left], c = G[t][right];
	int p = P[s];
	if(P[s] != -1)
	{
		if(G[p][left] == s) G[p][left] = t;
		if(G[p][right] == s) G[p][right] = t;
	}
	P[t] = p;
	if(P[t] == -1) root = t;
	G[t][left] = s, P[s] = t, G[t][right] = c, P[c] = t;
	G[s][left] = a, P[a] = s, G[s][right] = b, P[b] = s;
	fix(root, 0);
}
void rotate_right(int t)
{
	int s = G[t][left];
	int a = G[s][left], b = G[s][right], c = G[t][right];
	int p = P[t];
	if(P[t] != -1)
	{
		if(G[p][left] == t) G[p][left] = s;
		if(G[p][right] == t) G[p][right] = s;
	}
	P[s] = p;
	if(P[s] == -1) root = s;
	G[s][left] = a, P[a] = s, G[s][right] = t, P[t] = s;
	G[t][left] = b, P[b] = t, G[t][right] = c, P[c] = t;
	fix(root, 0);
}

bool test()
{
	for(int v = 0; v < 2 * N - 1; v++)
	{
		if(G[v].empty()) continue;
		int l = G[v][left], r = G[v][right];
		if(!G[l].empty())
		{
			if(total[G[l][left]] > total[G[v][right]])
			{
				rotate_right(v);
				return false;
			}
		}
		if(!G[r].empty())
		{
			if(total[G[r][right]] > total[G[v][left]])
			{
				rotate_left(v);
				return false;
			}
		}
	}
	return true;
}

void printtree(int v)
{
	cout << v << '(';
	if(!G[v].empty())
	{
		printtree(G[v][left]);
		printtree(G[v][right]);
	}
	cout << ')';
	if(v == 0) cout << endl;
}

void print(int v, string p)
{
	if(G[v].empty()) cout << p << '\n';
	else
	{
		print(G[v][left], p + '0');
		print(G[v][right], p + '1');
	}
}

int main()
{
	freopen("codes.in", "r", stdin); freopen("codes.out", "w", stdout);
	cin >> N;

	P[0] = -1;
	for(int i = 0; i < N - 1; i++)
	{
		G[2 * i].push_back(2 * i + 2);
		P[2 * i + 2] = 2 * i;
		G[2 * i].push_back(2 * i + 1);
		P[2 * i + 1] = 2 * i;
	}

	cin >> val[2 * N - 2];
	for(int i = N - 2; i >= 0; i--) cin >> val[2 * i + 1];

	/*printtree(0);
	rotate_right(2);
	printtree(0);

	print(0, "");*/

	fix(root, 0);
	while(!test());

	//cout << w_total[root];
	print(root, "");
}
