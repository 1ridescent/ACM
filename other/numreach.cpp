#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = 5050;

int N;
vector<int> G[MAX];
int num[MAX];

bool visited[MAX];
bool contains[MAX];
void dfs(int v)
{
	visited[v] = true;
	num[v] = 1;

	for(int i = 0; i < G[v].size(); i++)
	{
		int w = G[v][i];
		if(!visited[w]) dfs(w);

		num[v] += num[w];
		if(i > 0) // overcount: subtract
		{
			vector<int> paths;
			int left_v = G[v][i - 1], right_v = G[v][i];
			int intersect; // intersection of paths
			while(true)
			{
				if(left_v != -1)
				{
					if(contains[left_v])
					{
						intersect = left_v;
						break;
					}
					else
					{
						contains[left_v] = true;
						paths.push_back(left_v);
					}
					if(left_v == N) left_v = -1;
					else left_v = G[left_v].back();
				}
				if(right_v != -1)
				{
					if(contains[right_v])
					{
						intersect = right_v;
						break;
					}
					else
					{
						contains[right_v] = true;
						paths.push_back(right_v);
					}
					if(right_v == N) right_v = -1;
					else right_v = G[right_v].front();
				}
			}

			num[v] -= num[intersect];

			for(int i = 0; i < paths.size(); i++) contains[paths[i]] = false; // reset
		}
	}
}

int main()
{
	cin >> N;
	for(int v = 1; v <= N - 1; v++)
	{
		int K;
		cin >> K;
		for(int k = 0; k < K; k++)
		{
			int w;
			cin >> w;
			G[v].push_back(w);
		}
	}

	memset(visited, 0, sizeof(visited));
	memset(contains, 0, sizeof(contains));
	dfs(1);

	for(int v = 1; v <= N; v++)
	{
		cout << v << ' ' << num[v] << endl;
	}
	return 0;
}
