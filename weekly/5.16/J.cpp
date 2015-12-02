#include <bits/stdc++.h>

using namespace std;

vector<int> G[205];
vector<pair<int, int> > E;
void add_edge(int u, int v)
{
	E.push_back(make_pair(u, v));
	G[u].push_back(v);
	G[v].push_back(u);
}

int random_walk(int s, int t)
{
	int cnt = 0;
	while(s != t)
	{
		s = G[s][rand() % G[s].size()];
		cnt++;
	}
	return cnt;
}

#define THR 150

int N, K;
int main()
{
	srand(time(0));
	cin >> N >> K;
	if(N == 3)
	{
		add_edge(1, 2);
		add_edge(2, 3);
	}
	else
	{
		for(int i = 1; i <= THR; i++)
			for(int j = i + 1; j <= THR; j++)
				add_edge(i, j);
		for(int i = THR + 1; i <= 200; i++)
			add_edge(i - 1, i);
	}
		cout << E.size () << endl;
		for(int i = 0; i < E.size(); i++)
			printf("%d %d\n", E[i].first, E[i].second);
	/*int sum = 0;
	for(int i = 0; i < 20; i++)
	{
		int t = random_walk(1, 200);
		cout << t << endl;
		sum += t;
	}
	cout << sum / 20 << endl;*/
}
