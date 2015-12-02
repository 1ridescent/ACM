#include <bits/stdc++.h>

using namespace std;

const int inf = 1000000;

int N;
int dist[105][105];

int K;
int path[105];
int len[105][105];

int mane()
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			cin >> dist[i][j];
			if(i != j && dist[i][j] == 0)
				dist[i][j] = inf;
		}
	cin >> K;
	for(int i = 0; i < K; i++) cin >> path[i];
	for(int s = 0; s < K; s++)
		for(int t = s + 1; t < K; t++)
		{
			len[s][t] = 0;
			for(int i = s; i < t; i++)
				len[s][t] += dist[path[i]][path[i + 1]];
		}
	for(int k = 0; k < N; k++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	int ans = 0, last_i = 0;
	for(int t = 1; t < K; t++)
	{
		bool bad = false;
		for(int s = last_i; s < t; s++)
		{
			//printf("s=%d t=%d len=%d from=%d to=%d dist=%d\n", s, t, len[s][t], path[s], path[t], dist[path[s]][path[t]]);
			if(len[s][t] > dist[path[s]][path[t]])
				bad = true;
		}
		if(bad)
		{
			ans++;
			last_i = t;
		}
	}
	cout << ans << '\n';
}

int main()
{
	for(int i = 1; ; i++)
	{
		cin >> N;
		if(N == 0) break;
		cout << "Case " << i << ": ";
		mane();
	}
}
