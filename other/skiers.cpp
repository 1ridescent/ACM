#include <iostream>
#include <vector>
#include <cstring>
#include <deque>

using namespace std;

int N;
vector<int> G[5050];
int next[5050];
deque<int> from[5050];
bool visited[5050];

void dfs(int u)
{
	visited[u] = true;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		from[v].push_back(u);
		if(!visited[v]) dfs(v);
	}
}

bool contains[5050];
bool valid(int u, int j)
{
	int u0 = u;
	int v = G[u][j + 1];
	//cout << "testing " << u << ' ' << v << "...\n";
	vector<int> path;
	while(true)
	{
		//cout << "from[" << v << "][0] = " << from[v][0] << endl;
		path.push_back(v);
		if(v == N) break;
		u = v;
		v = G[v][0];
	}

	for(int i = 0; i < path.size(); i++) contains[path[i]] = true;

	bool ans;
	u = u0;
	v = G[u][j];
	while(true)
	{
		if(!visited[v])
		{
			ans = false;
			break;
		}
		if(contains[v])
		{
			ans = visited[v];
			break;
		}
		for(int i = 0; i < G[u].size(); i++)
		{
			if(!visited[G[u][i]])
			{
				ans = false;
				break;
			}
		}
		u = v;
		v = G[v].back();
	}

	for(int i = 0; i < path.size(); i++) contains[path[i]] = false;
	//cout << "verdict = " << ans << endl;
	return ans;
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N - 1; i++)
	{
		int K;
		cin >> K;
		for(int k = 0; k < K; k++)
		{
			int v;
			cin >> v;
			G[i].push_back(v);
			next[i] = -1;
		}
	}

	memset(visited, 0, sizeof(visited));
	dfs(1);
	//for(int i = 1; i <= N; i++) { for(int j = 0; j < from[i].size(); j++) cout << from[i][j] << ' '; cout << endl; }

	memset(contains, 0, sizeof(contains));
	memset(visited, 0, sizeof(visited));
	int numvisited = 1;
	visited[N] = true;
	int cnt = 0;
	while(true)
	{
		bool rightmost = true;
		int u = 1;
		while(u != N)
		{
			cout << u << ' ';
			if(next[u] == -1 || next[u] < G[u].size() - 1 && valid(u, next[u])) next[u]++;
			if(next[u] < G[u].size() - 1) rightmost = false;
			int v = G[u][next[u]];
			/*if(from[v][0] == u)
			{
				//cout << "removed " << from[v][0] << ' ' << v << endl;
				from[v].pop_front();
			}*/
			if(!visited[u])
			{
				//cout << u << " now visited\n";
				visited[u] = true;
				numvisited++;
			}
			u = v;
		}
		//for(int i = 1; i <= N; i++) cout << visited[i]; cout << endl;
		cout << N << endl;
		//cout << "numvisited = " << numvisited << endl;
		cnt++;
		if(rightmost) break;
	}
	cout << cnt << endl;
	return 0;
}
