#include <bits/stdc++.h>

using namespace std;

const int MAX = 7010;

vector<int> G[MAX];
int cap[MAX][MAX];
int from[MAX];
queue<int> Q;
int augment_path(int s, int t)
{
	memset(from, -1, sizeof(from));

	from[s] = s;
	Q.push(s);
	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for(int v : G[u])
		{
			if(from[v] != -1) continue;
			if(cap[u][v] == 0) continue;
			from[v] = u;
			Q.push(v);
		}
	}
	if(from[t] == -1) return 0;

	int flow = cap[from[t]][t];
	for(int v = t; v != s; v = from[v])
	{
		int u = from[v];
		flow = min(flow, cap[u][v]);
	}

	for(int v = t; v != s; v = from[v])
	{
		int u = from[v];
		cap[u][v] -= flow;
		cap[v][u] += flow;
	}

	return flow;
}
int max_flow(int s, int t)
{
	int flow = 0;
	while(true)
	{
		int add = augment_path(s, t);
		if(add == 0) break;
		flow += add;
	}
	return flow;
}
void add_edge(int u, int v, int c)
{
	//printf("adding %d -> %d\n", u, v);
	G[u].push_back(v);
	G[v].push_back(u);
	cap[u][v] += c;
}

#define SRC 7004
#define SNK 7006

#define RAW(i) (i)
#define FACT(i) (1000 + (i))
#define STATE(i) (2000 + (i))
#define TRANS_IN(i) (3000 + (i))
#define TRANS_OUT(i) (4000 + (i))

int S, R, F, T;
map<string, pair<char, int> > state_map;

pair<char, int> get_id(string s, char c)
{
	if(!state_map.count(s)) state_map[s] = make_pair(c, state_map.size() + 1);
	return state_map[s];
}

int main()
{
	cin >> S >> R >> F >> T;
	for(int i = 0; i < R; i++)
	{
		string s;
		cin >> s;
		add_edge(SRC, RAW(get_id(s, 'r').second), 1);
	}
	for(int i = 0; i < F; i++)
	{
		string s;
		cin >> s;
		add_edge(FACT(get_id(s, 'f').second), SNK, 1);
	}
	for(int t = 1; t <= T; t++)
	{
		add_edge(TRANS_IN(t), TRANS_OUT(t), 1);
		int n;
		cin >> n;
		while(n--)
		{
			string s;
			cin >> s;
			pair<char, int> p = get_id(s, '.');
			char c = p.first;
			int i = p.second;
			if(c == 'r') add_edge(RAW(i), TRANS_IN(t), 1);
			else if(c == 'f') add_edge(TRANS_OUT(t), FACT(i), 1);
			else
			{
				add_edge(TRANS_OUT(t), STATE(i), 1);
				add_edge(STATE(i), TRANS_IN(t), 1);
			}
		}
	}
	cout << max_flow(SRC, SNK) << endl;
}
