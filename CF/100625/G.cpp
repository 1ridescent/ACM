#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> point;
#define x first
#define y second
#define SQ(x) ((x) * (x))

double W;
int N;
point S[1005];
double R[1005];
double dist[1005][1005];
bool poss[1005][1005];
bool start[1005], end[1005];
bool vis[1005];

bool dfs(int u)
{
	//cout << "dfs at " << u << endl;
	vis[u] = true;
	if(end[u]) return true;
	for(int v = 0; v < N; v++)
		if(!vis[v] && poss[u][v] && dfs(v)) return true;
	return false;
}
bool test(double width)
{
	memset(start, 0, sizeof(start));
	memset(end, 0, sizeof(end));
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
			poss[i][j] = (dist[i][j] < width);
		double w = R[i] + width;
		if(S[i].x - w < 0) start[i] = true;
		if(S[i].x + w > W) end[i] = true;
	}
	//cout << "testing " << width << " : " << start[0] << ' ' << end[1] << ' ' << dist[0][1] << endl;
	memset(vis, 0, sizeof(vis));
	bool cut = false;
	for(int i = 0; i < N; i++)
		if(!vis[i] && start[i])
			cut = (cut || dfs(i));
	return !cut;
}

int main()
{
	ios::sync_with_stdio(false);
	int tests;
	cin >> tests;
	while(tests--)
	{
		cin >> W >> N;
		for(int i = 0; i < N; i++)
			cin >> S[i].x >> S[i].y >> R[i];
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				dist[i][j] = sqrt(SQ(S[i].x - S[j].x) + SQ(S[i].y - S[j].y)) - R[i] - R[j];
		double low = 0.0, high = W;
		while(low + 1e-8 < high)
		{
			double mid = (low + high) / 2;
			if(test(mid)) low = mid;
			else high = mid;
		}
		printf("%.7f\n", low / 2.0);
	}
}
