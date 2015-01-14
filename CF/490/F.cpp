#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int A[6005];
vector<int> G[6005];

bool child[6005][6005];
vector<short> subtree[6005];

void calc_child(int u, int p)
{
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		child[u][v] = true;
		calc_child(v, u);
		for(int j = 1; j <= N; j++)
			child[u][j] |= child[v][j];
	}
}

int up[6005], down[6005];

int calc_data(int u, int p, int* data) // up
{
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		calc_data(v, u, data);
	}
	int best = 0;
	for(int i = 0; i < subtree[u].size(); i++)
	{
		int v = subtree[u][i];
		if(A[u] < A[v])
			best = max(best, data[v]);
	}
	data[u] = 1 + best;
}

int ans[6005];
void calc_ans(int u, int p)
{
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		calc_ans(v, u);
	}

	int best = 0;
	for(int i1 = 0; i1 < G[u].size(); i1++)
	{
		int v1 = G[u][i1];
		if(v1 == p) continue;
		for(int i2 = 0; i2 < G[u].size(); i2++)
		{
			if(i1 == i2) continue;
			int v2 = G[u][i2];
			if(v2 == p) continue;
			for(int i = 0; i < subtree[v1].size(); i++)
				for(int j = 0; j < subtree[v2].size(); j++)
				{
					int v = subtree[v1][i];
					int w = subtree[v2][j];
					//cout << u << ' ' << v << ' ' << w << endl;
					if(A[v] < A[w])
					{
						int val = down[v] + up[w];
						if(A[v] < A[u] && A[u] < A[w]) // include u
							val++;
						best = max(best, val);
					}
				}
		}
	}
	ans[u] = best;
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 1; i < N; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	memset(child, 0, sizeof(child));
	calc_child(1, -1);
	for(int u = 1; u <= N; u++)
		for(int v = 1; v <= N; v++)
			if(child[u][v] || u == v)
				subtree[u].push_back(v);
	//for(int i = 1; i <= N;i ++) cout << children[i].size() << ' '; cout << endl;

	calc_data(1, -1, up);
	for(int i = 1; i <= N; i++) A[i] *= -1;
	calc_data(1, -1, down);
	for(int i = 1; i <= N; i++) A[i] *= -1;
	//for(int i = 1; i <= N; i++) cout << i << ':' << up[i] << ' '; cout << endl;

	calc_ans(1, -1);

	int res = 0;
	for(int i = 1; i <= N; i++)
		res = max(res, max(up[i], down[i]));
	for(int i = 1; i <= N; i++)
		res = max(res, ans[i]);
	cout << res;
}
