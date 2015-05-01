#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 17);
const int LGMAX = 17;

vector<int> G[MAX];
int deg[MAX];

void dfs(int u, int p)
{
	deg[u] = G[u].size();
	for(int i = 0; i < G[u].size(); i++)
		if(G[u][i] == p)
		{
			G[u].erase(G[u].begin() + i);
			break;
		}
	for(int i = 0; i < G[u].size(); i++)
		dfs(G[u][i], u);
}

int jump[MAX][LGMAX];
void get_jump(int u, int p)
{
	int i = 0;
	while(p != -1)
	{
		jump[u][i] = p;
		p = jump[p][i];
		i++;
	}
	for(int i = 0; i < G[u].size(); i++)
		get_jump(G[u][i], u);
}

int SA[MAX];
int rank[MAX];
int next[MAX];
int temp[MAX];
bool cmp(int i, int j)
{
	return deg[i] < deg[j];
}
void get_suffix_array()
{
	for(int i = 0; i < N; i++)
		SA[i] = i;
	sort(SA, SA + N, cmp);

	rank[SA[0]] = 0;
	for(int i = 0; i < N - 1; i++)
	{
		if(deg[SA[i]] == deg[jump[SA[i]][0]])
			rank[SA[i + 1]] = rank[SA[i]];
		else
			rank[SA[i + 1]] = i + 1;
	}
	for(int l = 0; ; l++)
	{
		int len = (1 << l);
		if(len >= N) break;
		for(int i = 0; i < N; i++)
			next[i] = i;
		for(int i = 0; i < N; i++)
			temp[next[rank[SA[i] - len]]++] = SA[i] - len;
		for(int i = 0; i < N; i++)
			if(SA[i] >= len)
				temp[next[rank[SA[i] - len]]++] = SA[i] - len;
		memcpy(SA, temp, sizeof(temp));
		temp[SA[0]] = 0;
		for(int i = 0; i < N - 1; i++)
		{
			if(SA[i] + len < N && SA[i + 1] + len < N && rank[SA[i]] == rank[SA[i + 1]] && rank[SA[i] + len] == rank[SA[i + 1] + len])
				temp[SA[i + 1]] = temp[SA[i]];
			else
				temp[SA[i + 1]] = i + 1;
		}
	}
}

int main()
{
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].push_back(v);
	}
	dfs(0, -1);
	memset(jump, -1, sizeof(jump);
	get_jump(0, -1);
	get_suffix_array();
}
