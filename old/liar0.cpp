#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int INF = 123123123;

vector<int> G[500500];
int G2[500500];
int cycle_id[500500]; // which cycle does v belong in
int cycle_first[500500];
int cycle_cut[500500]; // cut edge of this cycle
int cycle_next = 1; // next cycle id
set<int> cur_cycles;
int val[500500];
bool is_root[500500];

int depth[500500]; // root has depth 0
int path[500500][20]; // [v][d] means jump from v up 2^d nodes
int largest[500500][20]; // largest node in jump from v up 2^d nodes, excluding final node
void setup_dfs(int v, int p, int d)
{
    depth[v] = d;
    int last = p;
    int maxval = val[v];
    for(int i = 0; (1<<i) <= d; i++)
    {
        path[v][i] = last;
        largest[v][i] = maxval;
        maxval = max(maxval, largest[last][i]);
        last = path[last][i];
    }
    for(int i = 0; i < G[v].size(); i++)
    {
        int w = G[v][i];
        setup_dfs(w, v, d+1);
    }
}
void setup_lca() // 1 is the root
{
    for(int i = 0; i < 500500; i++) if(is_root[i]) setup_dfs(i, -1, 0);
}
int jump(int v, int d) // jump from v up d nodes
{
    for(int i = 0; i < 20; i++)
    {
        if(d & (1<<i)) v = path[v][i];
    }
    return v;
}
int maxjump(int v, int d) // max in jump from v up d nodes
{
    int maxval = val[v];
    for(int i = 0; i < 20; i++)
    {
        if(d & (1<<i))
        {
            maxval = max(maxval, largest[v][i]);
            v = path[v][i];
        }
    }
    return maxval;
}
int maxjumpto(int s, int f)
{
    int d = depth[s] - depth[f];
    return maxjump(s, d);
}
int lca(int v, int w)
{
    if(depth[v] < depth[w]) return lca(w, v);
    v = jump(v, depth[v] - depth[w]);
    int d = depth[v];
    for(int i = 19; i >= 0; i--)
    {
        if((1<<i) > d) continue;
        if(jump(v, 1<<i) != jump(w, 1<<i))
        {
            v = jump(v, 1<<i), w = jump(w, 1<<i);
        }
    }
    if(v == 1) return 1;
    return jump(v, 1);
}

pair<int,int> dfsorder[500500][2]; // start/finish times
int dfsnumber = 1;
int dfstime = 1;
void dfs(int v)
{
    dfsorder[v][0] = make_pair(dfsnumber, dfstime);
    dfstime++;
    for(int i = 0; i < G[v].size(); i++)
    {
        int w = G[v][i];
        dfs(w);
    }
    dfsorder[v][1] = make_pair(dfsnumber, dfstime);
    dfstime++;
}
void get_dfsorders()
{
    for(int i = 0; i < 500500; i++)
    {
        if(is_root[i]) dfs(i);
        dfsnumber++;
    }
}

map< pair<int,int>, int > S;
vector<int> T;
vector<int> F;

bool cmp(int t1, int t2)
{
    return dfsorder[t1][0] > dfsorder[t2][0];
}
int process()
{
    map< pair<int,int>, int > M; // for false
    for(int i = 0; i < F.size(); i++)
    {
        M[dfsorder[F[i]][0]] = F[i];
    }
    sort(T.begin(), T.end(), cmp); // start with latest
    int first = INF;
    for(int i = 0; i < T.size(); i++)
    {
        int t = T[i];
        pair<int,int> start = dfsorder[t][0], finish = dfsorder[t][1];
        for(map<pair<int,int>, int>::iterator it = M.lower_bound(start); it != M.upper_bound(finish); it++)
        {
            int f = it->second;
            //cout << f << " goes to " << t << endl;
            first = min(first, maxjumpto(f, t));
        }
        M.erase(M.lower_bound(start), M.upper_bound(finish));
    }
    M.clear();

    // now check cycles...
    for(int i = 0; i < T.size(); i++)
    	if(cycle_id[T[i]] != -1) cur_cycles.insert(cycle_id[T[i]]);
    for(int i = 0; i < F.size(); i++)
    	if(cycle_id[F[i]] != -1 && cur_cycles.find(cycle_id[F[i]]) != cur_cycles.end()) first = min(first, cycle_cut[cycle_id[F[i]]]);
    cur_cycles.clear();

    return (first == INF ? -1 : first);
}

int R[500500];

void init_UF()
{
    for(int i = 0; i < 500500; i++) R[i] = -1;
}
int Find(int v)
{
    if(R[v] < 0) return v;
    return Find(R[v]);
}
void Union(int u, int v)
{
    int Ru = Find(u), Rv = Find(v);
    if(-R[Ru] < -R[Rv]) R[Ru] = Rv;
    else if(-R[Ru] > -R[Rv]) R[Rv] = Ru;
    else
    {
        R[Ru] = Rv;
        R[Rv]--;
    }
}

int main()
{
    int N;
    cin >> N;
    for(int i = 0; i < 500500; i++) is_root[i] = true;
    for(int i = 0; i < 500500; i++) cycle_id[i] = -1;
    init_UF();
    for(int i = 1; i <= N; i++)
    {
        int a, b;
        cin >> a >> b;
        if(Find(a) == Find(b)) // cycle
        {
        	for(int v = a; v != b; v = G2[v]) cycle_id[v] = cycle_next;
        	cycle_id[b] = cycle_next;
        	cycle_cut[cycle_next] = i;
        	cycle_next++;
            //cout << "cycle from " << a << " to " << b << endl;
        }
        else
        {
            G[a].push_back(b);
            G2[b] = a;
            val[b] = i;
            is_root[b] = false;
            Union(a, b);
        }
    }
    setup_lca();
    get_dfsorders();
    int Q;
    cin >> Q;
    for(int q = 0; q < Q; q++)
    {
        S.clear();
        T.clear();
        F.clear();
        int Nt, Nf, v;
        cin >> Nt;
        for(int i = 0; i < Nt; i++)
        {
            cin >> v;
            T.push_back(v);
        }
        cin >> Nf;
        for(int i = 0; i < Nf; i++)
        {
            cin >> v;
            F.push_back(v);
        }
        cout << process() << '\n';
    }
    return 0;
}
