#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int INF = 1231231231;
const int MAX = 110;

int N, M;
vector<int> G[MAX];
int C[MAX][MAX];
int from[MAX];
const int S = 102, S1 = 103, T = 104, T1 = 105;

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
int max_flow(int s, int t)
{
	int flow = 0, add;
	do
	{
		add = augment_path(s, t);
		flow += add;
	}
	while(add > 0);
	return flow;
}
void print()
{
	for(int i = 0; i < MAX; i++)
	{
		for(int j = 0; j < G[i].size(); j++)
		{
			cout << i << " -> " << G[i][j] << " = " << C[i][j] << "/" << C[i][j] + C[j][i] << endl;
		}
	}
}

int C0[MAX][MAX];
struct edge
{
	int u, v, b, c;
};
edge E[10005];
map<int, vector<int> > res;

int main()
{
	memset(C, 0, sizeof(C));
	cin >> N >> M;
	int total = 0;
	for(int i = 0; i < M; i++)
	{
		int u, v, c, b;
		cin >> u >> v >> c >> b;
		E[i].u = u, E[i].v = v, E[i].b = b, E[i].c = c;
		if(!b)
		{
			add_edge(u, v, c);
		}
		else
		{
			add_edge(u, T, c);
			add_edge(S, v, c);
			total += c;
		}
	}

	add_edge(N, 1, 0);

	memcpy(C0, C, sizeof(C));
	int found = -1;
	int low = -1, high = 20000005;
	while(low + 1 < high)
	{
		memcpy(C, C0, sizeof(C));
		int mid = (low + high) / 2;
		C[N][1] = mid;
		//C[1][N] = mid;
		//add_edge(S, 1, mid);
		//add_edge(N, T, mid);
		int flow = max_flow(S, T);
		//cout << mid << ": " << flow << endl;
		if(flow == total)
		{
			high = mid;
			found = mid;
			for(int i = 0; i < M; i++) res[mid].push_back(C[E[i].v][E[i].u]);
			//for(int i = 0; i < M; i++) cout << res[high][i] << ' ';
			//print();
		}
		else
		{
			low = mid;
		}
	}
	if(found == -1) cout << "Impossible\n";
	else
	{
		cout << found << endl;
		for(int i = 0; i < M; i++) cout << (E[i].b ? E[i].c : res[found][i]) << (i == M - 1 ? '\n' : ' ');
	}
}
