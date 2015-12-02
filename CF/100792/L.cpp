#include <bits/stdc++.h>

using namespace std;

int N, M, len, K;

int from[505], to[505];
int num[505];
int nxt[505][2];

const int MAX = (505 * 5000);
#define NODE(s, b) (((s) * 5000) + b)
bool finished[MAX];

bool used[505];
bool is_valid(int s, int b)
{
	printf("trying s=%d b=%d\n", s, b);
	memset(used, 0, sizeof(used));
	bool ans = true;
	int r = s;
	if(from[r] == N || to[r] == N)
	{
		finished[NODE(s, b)] = true;
		return true;
	}
	for(int i = 0; i < K; i++)
	{
		if(used[from[r]]) return false;
		used[from[r]] = true;
		int d = !!(b & (1 << i));
		printf("cur r = %d num=%d d=%d\n", r, num[r], d);
		if(d >= num[r]) return false;
		r = nxt[r][d];
		if(to[r] == N)
		{
			cout << NODE(s, b) << " is finished\n";
			finished[NODE(s, b)] = true;
			return true;
		}
	}
	return true;
}

vector<int> G[MAX];
queue<int> Q;
int dist[MAX];
int bfs()
{
	for(int i = 0; i < MAX; i++)
		if(dist[i] != -1)
			Q.push(i);
	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for(int v : G[u])
		{
			if(dist[v] == -1)
			{
				dist[v] = dist[u] + 1;
				Q.push(v);
			}
		}
	}
}

int main()
{
	cin >> N >> M >> len;
	K = (len - 1) / 40; // number of segment need to keep track
	for(int i = 1; i <= M; i++)
	{
		cin >> from[i] >> to[i];
		cin >> num[i] >> nxt[i][0];
		if(num[i] == 2) cin >> nxt[i][1];
	}
	for(int s = 1; s <= M; s++)
		for(int b = 0; b < (1 << K); b++)
			if(is_valid(s, b))
				for(int i = 0; i < num[s]; i++)
				{
					int s2 = nxt[s][i];
					int b2 = ((b >> 1) | (i << (K - 1)));
					if(is_valid(s2, b2))
					{
						G[NODE(s, b)].push_back(NODE(s2, b2));
						cout << NODE(s, b) << " -> " << NODE(s2, b2) << endl;
					}
				}
	memset(dist, -1, sizeof(dist));
	for(int b = 0; b < (1 << K); b++)
		if(is_valid(1, b))
		{
			cout << "start at " << NODE(1, b) << endl;
			dist[NODE(1, b)] = 0;
		}
	bfs();
	int ans = MAX;
	for(int i = 0; i < MAX; i++)
		if(finished[i] && dist[i] != -1)
		{
			cout << i << " finished\n";
			ans = min(ans, dist[i]);
		}
	cout << ans << endl;
	cout << ans * 1000 + K * 1000 + len * 25 << endl;
}
