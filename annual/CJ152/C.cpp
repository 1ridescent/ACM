#include <bits/stdc++.h>

using namespace std;

/***** MAX-FLOW *****/

const int MAX = 8010;
#define SRC 8005
#define SNK 8006
#define IN(v) (v)
#define OUT(v) ((v) + 4000)

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
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
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
void init()
{
	memset(cap, 0, sizeof(cap));
	for(int i = 0; i < MAX; i++) G[i].clear();
}
void add_edge(int u, int v, int c)
{
	G[u].push_back(v);
	G[v].push_back(u);
	cap[u][v] += c;
}

int N;
map<string, int> id;
int get_id(string s)
{
	if(id.count(s)) return id[s];
	int i = id.size();
	id[s] = i;
	return i;
}

vector<int> E, F;
vector<pair<int, int> > A;
bool adj[MAX][MAX];

int main2()
{
	id.clear(); E.clear(); F.clear(); A.clear();
	string input;
	cin >> N;
	getline(cin, input);
	while(cin.peek() != '\n')
	{
		cin >> input;
		int v = get_id(input);
		E.push_back(v);
		//cout << "E " << input << endl;
	}
	getline(cin, input);
	while(cin.peek() != '\n')
	{
		cin >> input;
		int v = get_id(input);
		F.push_back(v);
		//cout << "F " << input << endl;
	}
	getline(cin, input);
	for(int t = 2; t < N; t++)
	{
		vector<int> v;
		while(cin.peek() != '\n')
		{
			cin >> input;
			int vv = get_id(input);
			v.push_back(vv);
		}
		getline(cin, input);
		for(int i = 0; i < v.size(); i++)
			for(int j = 0; j < v.size(); j++)
				A.push_back(make_pair(v[i], v[j]));
	}

	init();
	for(int i = 0; i < E.size(); i++)
		add_edge(SRC, IN(E[i]), MAX);
	for(int i = 0; i < F.size(); i++)
		add_edge(OUT(F[i]), SNK, MAX);
	memset(adj, 0, sizeof(adj));
	for(int i = 0; i < A.size(); i++)
	{
		int u = A[i].first, v = A[i].second;
		if(u != v && !adj[u][v])
		{
			adj[u][v] = true;
			add_edge(OUT(u), IN(v), MAX);
		}
	}
	cout << "id size = " << id.size() << endl;
	for(int i = 0; i < id.size(); i++)
		add_edge(IN(i), OUT(i), 1);
	cout << max_flow(SRC, SNK) << '\n';
}


int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cout << "Case #" << t << ": ";
		main2();
	}
}
