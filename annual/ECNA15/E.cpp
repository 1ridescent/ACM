#include <bits/stdc++.h>

using namespace std;

int N, M, S, T;
vector<int> G[1005];
long long V[1005][1005];

int main()
{
	cin >> N >> M >> S >> T;
	while(M--)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	long long ans = 0;
	V[0][S] = 1;
	for(int t = 1; t <= T + 1; t++)
	{
		for(int i = 0; i < N; i++)
			for(int j : G[i])
			{
				V[t][j] += V[t - 1][i];
				if(t == T) ans += V[t - 1][i];
			}
		//for(int i = 0; i < N; i++) cout << i << ' ' << V[t][i] << "  "; cout << endl;
	}
	cout << ans << endl;
}
