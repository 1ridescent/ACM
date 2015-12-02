#include <bits/stdc++.h>

using namespace std;

int N, M;
int A[404][404];

queue<int> Q; // (1/2, u1, u2)
bool vis[3][404][404];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			if(i != j) A[i][j] = 1;
	A[N][N] = 3;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		A[a][b] = A[b][a] = 2;
	}
	vis[1][1][1] = true;
	Q.push(1); Q.push(1); Q.push(1); Q.push(0);
	while(!Q.empty())
	{
		int t = Q.front(); Q.pop();
		int u1 = Q.front(); Q.pop();
		int u2 = Q.front(); Q.pop();
		int d = Q.front(); Q.pop();
		if(t == 1 && u1 == N && u2 == N)
		{
			cout << d << endl;
			return 0;
		}
		if(t == 1)
		{
			for(int v1 = 1; v1 <= N; v1++)
				if((A[u1][v1] & 1) && !vis[2][v1][u2])
				{
					vis[2][v1][u2] = true;
					Q.push(2); Q.push(v1); Q.push(u2); Q.push(d);
				}
		}
		else
		{
			for(int v2 = 1; v2 <= N; v2++)
				if((A[u2][v2] & 2) && !vis[1][u1][v2] && (v2 == N || u1 != v2))
				{
					vis[1][u1][v2] = true;
					Q.push(1); Q.push(u1); Q.push(v2); Q.push(d + 1);
				}
		}
	}
	cout << -1 << endl;
	return 0;
}
