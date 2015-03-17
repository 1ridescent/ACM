#include <bits/stdc++.h>

using namespace std;

const int MAX = 1111;
const int INF = 11111;

struct SCC
{
        int N, cnt, cmpt;
        int num[MAX], low[MAX], ans[MAX];
        vector<int> G[MAX];
        vector<int> S; // stack
        bool on_stack[MAX];

        void reset()
        {
                for(int i = 0; i < MAX; i++) G[i].clear();
        }
        void strong(int u)
        {
                if(num[u] != 0) return;
                num[u] = low[u] = ++cnt;
                S.push_back(u);
                on_stack[u] = true;
                for(int i = 0; i < G[u].size(); i++)
                {
                        int v = G[u][i];
                        strong(v);
                }
                for(int i = 0; i < G[u].size(); i++)
                {
                        int v = G[u][i];
                        if(on_stack[v]) low[u] = min(low[u], low[v]);
                }
                if(num[u] == low[u])
                {
                        while(!S.empty())
                        {
                                int x = S.back();
                                S.pop_back();
                                on_stack[x] = false;
                                ans[x] = cmpt;
                                if(x == u) break;
                        }
                        cmpt++;
                }
        }
        void scc()
        {
                memset(num, 0, sizeof(num));
                memset(low, 0, sizeof(low));
                memset(ans, 0, sizeof(ans));
                memset(on_stack, 0, sizeof(on_stack));
                S.clear();
                cnt = 0;
                cmpt = 0;
                for(int i = 0; i < N; i++) strong(i);
        }
};

struct MinCostFlow
{
        vector<int> G[MAX];
        int cap[MAX][MAX];
        int cost[MAX][MAX];
        int pi[MAX];
        int dist[MAX];
        int from[MAX];

        void init()
        {
                memset(cap, 0, sizeof(cap));
                memset(cost, 0, sizeof(cost));
                for(int i = 0; i < MAX; i++) G[i].clear();
        }
        int mcf_until(int src, int snk, int target)
        {
                for(int i = 0; i < MAX; i++)
                        for(int j = 0; j < MAX; j++)
                                if(cap[i][j])
                                        cost[j][i] = -cost[i][j];

                memset(pi, 0, sizeof(pi));
                /*while(true)
                {
                	//cout << "..." << endl;
                	bool done = true;
                	for(int u = 0; u < MAX; u++)
                		for(int i = 0; i < G[u].size(); i++)
                		{
                			int v = G[u][i];
                			if(cap[u][v] && pi[u] + cost[u][v] < pi[v])
                			{
                				//cout << u << ' ' << v << endl;
                				pi[v] = pi[u] + cost[u][v];
                				done = false;
                			}
                		}
                	if(done) break;
                }*/

                int cst = 0;
                for(int f = 0; ; )
                {
                	//cout << "f = " <<f  << endl;
                        for(int i = 0; i < MAX; i++) dist[i] = INF;
                        memset(from, -1, sizeof(from));
                        dist[src] = 0, from[src] = -2;
                        priority_queue<pair<int, int> > q;
                        q.push(make_pair(0, src));
                        while(!q.empty())
                        {
                        	//cout << "queue" << q.size()<< endl;
                                pair<int, int> pr = q.top(); q.pop();
                                int best = pr.second;
                                if(abs(pr.first + dist[best]) > 0) continue;
                                for(int vi = 0; vi < (int)G[best].size(); vi++)
                                {
                                        int i = G[best][vi];
                                        if(cap[best][i] && dist[best] + cost[best][i] + pi[best] - pi[i] < dist[i])
                                        {
                                                dist[i] = dist[best] + cost[best][i] + pi[best] - pi[i];
                                                from[i] = best;
                                                q.push(make_pair(-dist[i], i));
                                        }
                                }
                        }
                        if(from[snk] == -1) return -1;
                        for(int i = 0; i < MAX; i++) if(from[i] == -1) pi[i] += dist[i];

                        int aug_f = 1;// flow - f;
                        //for(int v = snk; v != src; v = from[v])
                          //      aug_f = min(aug_f, cap[from[v]][v]);

                        for(int v = snk; v != src; v = from[v])
                        {
                                int u = from[v];
                                cap[u][v] -= aug_f;
                                cap[v][u] += aug_f;
                                cst += aug_f * cost[u][v];
                        }
                        f += aug_f;

                        if(cst == target) return f;
                }
                return -1;
        }

        void add_edge(int u, int v, int cp, int cst)
        {
        	//printf("%d %d %d %d\n", u, v, cp, cst);
                G[u].push_back(v);
                G[v].push_back(u);
            cap[u][v] = cp;
            cap[v][u] = 0;
            cost[u][v] = cst;
        }

};

MinCostFlow mcf;

int N, M;
SCC scc;
vector<pair<int, int> > E;
map<int, set<int> > D;
vector<int> G[MAX];
int size[MAX];
bool added[MAX][MAX];

#define SOURCE 1
#define SINK 2
#define IN(v) ((v) + 4)
#define OUT(v) ((v) + 506)

int main2()
{
	scc.reset();
	E.clear();
	D.clear();
	for(int i = 0; i < MAX; i++) G[i].clear();
	cin >> N >> M;
	scc.N = N;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		E.push_back(make_pair(a, b));
		scc.G[a].push_back(b);
	}
	scc.scc();
	//for(int i = 0; i < N; i++) cout << scc.ans[i] << ' '; cout << endl;
	memset(size, 0, sizeof(size));
	for(int i = 0; i < N; i++)
		size[scc.ans[i]]++;

	mcf.init();
	for(int i = 0; i < scc.cmpt; i++)
	{
		mcf.add_edge(SOURCE, IN(i), INF, 0);
		mcf.add_edge(IN(i), OUT(i), size[i], -1);
		mcf.add_edge(OUT(i), SINK, INF, 0);
	}
	memset(added, 0, sizeof(added));
	for(int i = 0; i < E.size(); i++)
	{
		int a = scc.ans[E[i].first], b = scc.ans[E[i].second];
		if(a == b) continue;
		//printf("%d %d\n", a, b);
		if(added[a][b]) continue;
		added[a][b] = true;
		mcf.add_edge(OUT(a), IN(b), INF, 0);
	}
	cout << mcf.mcf_until(SOURCE, SINK, -N) << endl;
}


int main()
{
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++)
	{
		printf("Case #%d: ", i);
		main2();
	}
}

