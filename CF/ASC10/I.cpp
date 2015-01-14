#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int INF = 1231231231;
const int MAX = 810;

vector<int> G[MAX];
int C[MAX][MAX];
int from[MAX];

int augment_path(int s, int t)
{
    for(int i = 0; i < MAX; i++) from[i] = -1;
    queue<int> Q;
    from[s] = 0;
    Q.push(s);
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if(u == t) // found an augmenting path
        {
            int flow = INF;
            int v = t;
            while(v != s)
            {
                u = from[v];
                flow = min(flow, C[u][v]);
                v = u;
            }
            v = t;
            while(v != s)
            {
                u = from[v];
                C[u][v] -= flow;
                C[v][u] += flow;
                v = u;
            }
            return flow;
        }
        for(int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i];
            if(from[v] != -1) continue; // already visited
            if(C[u][v] == 0) continue; // can't flow
            from[v] = u;
            Q.push(v);
        }
    }
    return 0;
}
void add_edge(int u, int v, int c)
{
    G[u].push_back(v);
    G[v].push_back(u);
    C[u][v] = c;
    C[v][u] = 0;
}

int N, M, P;
int S = 805, T = 806;

map<int, map<int, int> > edgeid;

vector<int> neighu[MAX], neighv[MAX];
vector<int> usedu[MAX], usedv[MAX];

int main()
{
	freopen("trade.in", "r", stdin); freopen("trade.out", "w", stdout);


	memset(C, 0, sizeof(C));
	cin >> N >> M >> P;
	for(int u = 1; u <= N; u++) add_edge(S, u, 2);
	for(int v = 1; v <= M; v++) add_edge(400 + v, T, 2);
	for(int i = 1; i <= P; i++)
	{
		int u, v;
		cin >> u >> v;
		neighu[u].push_back(v);
		neighv[v].push_back(u);
		add_edge(u, 400 + v, 1);
		edgeid[u][v] = i;
	}

	for(int u = 1; u <= N; u++)
	{
		if(neighu[u].size() < 2)
		{
			cout << "-1\n";
			return 0;
		}
	}
	for(int v = 1; v <= M; v++)
	{
		if(neighv[v].size() < 2)
		{
			cout << "-1\n";
			return 0;
		}
	}

	while(augment_path(S, T));

	for(int u = 1; u <= N; u++)
	{
		for(int v = 1; v <= M; v++)
		{
			if(C[400 + v][u] == 1)
			{
				usedu[u].push_back(v);
				usedv[v].push_back(u);
			}
		}
	}

	for(int u = 1; u <= N; u++)
	{
		if(usedu[u].size() < 2)
		{
			for(int vi = 0; vi < neighu[u].size(); vi++)
			{
				int v = neighu[u][vi];
				bool ok = true;
				for(int i = 0; i < usedu[u].size(); i++)
					if(v == usedu[u][i])
						ok = false;
				if(ok)
				{
					usedu[u].push_back(v);
					usedv[v].push_back(u);
				}
				if(usedu[u].size() == 2) break;
			}
		}
	}
	for(int v = 1; v <= M; v++)
	{
		if(usedv[v].size() < 2)
		{
			for(int ui = 0; ui < neighv[v].size(); ui++)
			{
				int u = neighv[v][ui];
				bool ok = true;
				for(int i = 0; i < usedv[v].size(); i++)
					if(u == usedv[v][i])
						ok = false;
				if(ok)
				{
					usedv[v].push_back(u);
					usedu[u].push_back(v);
				}
				if(usedv[v].size() == 2) break;
			}
		}
	}

	vector<int> res;
	for(int u = 1; u <= N; u++)
	{
		for(int i = 0; i < usedu[u].size(); i++)
		{
			res.push_back(edgeid[u][usedu[u][i]]);//(cout << u << ' ' << usedu[u][i] << endl;
		}
	}

	cout << res.size() << endl;
	for(int i = 0; i < res.size(); i++)
	{
		if(i > 0) cout << ' ';
		cout << res[i];
	}
}
