#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
vector<int> G[100100];
bool cur[100100];
bool goal[100100];

int dp[100100][4];

vector<int> res;

void compute(int v, int p, int b1, int b2)
{
	if((cur[v] ^ b1) == 0)
	{
		for(int i = 0; i < G[v].size(); i++)
		{
			int w = G[v][i];
			if(w == p) continue;
			compute(w, v, b2, b1);
		}
	}
	else
	{
		res.push_back(v);
		for(int i = 0; i < G[v].size(); i++)
		{
			int w = G[v][i];
			if(w == p) continue;
			compute(w, v, b2, !b1);
		}
	}
}

int main()
{
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i = 1; i <= N; i++) cin >> cur[i];
	for(int i = 1; i <= N; i++) cin >> goal[i];
	for(int i = 1; i <= N; i++) cur[i] ^= goal[i];
	compute(1, -1, 0, 0);
	cout << res.size() << '\n';
	for(int i = 0; i < res.size(); i++) cout << res[i] << '\n';
}
