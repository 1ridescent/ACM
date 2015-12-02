#include <bits/stdc++.h>

using namespace std;

int N;
bool A[505][505];

bool on_stack[505];
bool remove_cycle(int u, int p)
{
	on_stack[u] = true;
	//cout << u << endl;
	bool res = false;
	for(int v = 1; v <= N; v++)
		if(v != p && A[u][v])
		{
			if(on_stack[v])
			{
				cout << u << ' ' << v << endl;
				A[u][v] = false;
				A[v][u] = false;
				res = true;
				break;
			}
			else if(remove_cycle(v, u))
			{
				cout << u << ' ' << v << endl;
				A[u][v] = false;
				A[v][u] = false;
				res = true;
				break;
			}
		}
	on_stack[u] = false;
	return res;
}

bool vis[505];
int depth[505];
void dfs(int u, int d)
{
	depth[u] = d;
	vis[u] = true;
	for(int v = 1; v <= N; v++)
		if(A[u][v] && !vis[v])
			dfs(v, d + 1);
}

int main()
{
	int M;
	cin >> N >> M;
	while(M--)
	{
		int a, b;
		cin >> a >> b;
		A[a][b] = A[b][a] = true;
	}
	while(true)
	{
		bool restart = false;
		for(int i = 1; i <= N; i++)
			if(remove_cycle(i, -1))
				restart = true;
		if(!restart) break;
	}
	for(int i = 1; i <= N; i++)
		if(!vis[i])
			dfs(i, 0);
	for(int i = 1; i <= N; i++)
		cout << (depth[i] % 2 ? 'A' : 'B');
}
