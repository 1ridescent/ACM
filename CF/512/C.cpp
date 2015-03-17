#include <bits/stdc++.h>

using namespace std;

const int MAX = 222;

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
                for(int v = 0; v < MAX; v++)
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
void init()
{
        memset(cap, 0, sizeof(cap));
}
void add_edge(int u, int v, int c)
{
        cap[u][v] += c;
}

int N;
vector<pair<int, int> > odd, even;
#define ODD(i) (107 + (i))
#define EVEN(i) (4 + (i))
#define SOURCE 1
#define SINK 2

bool is_prime(int x)
{
	for(int i = 2; i * i <= x; i++)
		if(x % i == 0)
			return false;
	return true;
}

int ind[MAX];

bool used[MAX];
vector<vector<int> > V;

int main()
{
	int N;
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		int x;
		cin >> x;
		if(x % 2 == 0) even.push_back(make_pair(x, i));
		else odd.push_back(make_pair(x, i));
	}
	if(even.size() != odd.size())
	{
		cout << "Impossible";
		return 0;
	}
	for(int i = 0; i < N / 2; i++)
	{
		add_edge(SOURCE, ODD(i), 2);
		ind[ODD(i)] = odd[i].second;
	}
	for(int i = 0; i < N / 2; i++)
	{
		add_edge(EVEN(i), SINK, 2);
		ind[EVEN(i)] = even[i].second;
	}
	for(int i = 0; i < N / 2; i++)
		for(int j = 0; j < N / 2; j++)
			add_edge(ODD(i), EVEN(j), is_prime(odd[i].first + even[j].first));
	if(max_flow(SOURCE, SINK) != N)
	{
		cout << "Impossible";
		return 0;
	}
	for(int i = 0; i < N / 2; i++)
	{
		//cout << "at " << i << endl;
		if(used[ODD(i)]) continue;
		vector<int> v;
		int cur = i, prev = -1;
		v.push_back(ind[ODD(cur)]);
		used[ODD(cur)] = true;
		while(true)
		{
			int j;
			for(j = 0; j < N / 2; j++)
				if(!used[EVEN(j)] && cap[EVEN(j)][ODD(cur)])
				{
					//cout << "found " << j << endl;
					used[EVEN(j)] = true;
					v.push_back(ind[EVEN(j)]);
					break;
				}
			assert(j != N / 2);
			int i;
			for(i = 0; i < N / 2; i++)
				if(!used[ODD(i)] && cap[EVEN(j)][ODD(i)])
				{
					//cout << "found " << i << endl;
					used[ODD(i)] = true;
					v.push_back(ind[ODD(i)]);
					break;
				}
			if(i == N / 2) break;
			cur = i;
		}
		V.push_back(v);
	}
	cout << V.size() << endl;
	for(int i = 0; i < V.size(); i++)
	{
		cout << V[i].size();
		for(int j = 0; j < V[i].size(); j++) cout << ' ' << V[i][j];
		cout << endl;
	}
}
