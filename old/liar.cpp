#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int INF = 1000000000;
const int MAX = (1<<20);

struct edge
{
	int u, v, w;
};
struct MaxDistTree
{
	map< pair<int, int>, int > MST; // [u][v] -> w
	int R[MAX]; // representatives
	MaxDistTree()
	{
		for(int i = 0; i < MAX; i++) R[i] = -1;
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
	void add_edge(int u, int v, int w)
	{
		int Ru = Find(u), Rv = Find(v);
		if(Ru != Rv)
		{
			Union(Ru, Rv);
			MST[make_pair(Ru, Rv)] = w;
			MST[make_pair(Rv, Ru)] = w;
		}
	}
	int max_edge(int u, int v)
	{
		if(u == v) return 0;
	    int r = Find(u);
	    vector<int> pathu, pathv;
	    pathu.push_back(u);
	    while(u != r)
	    {
	        u = R[u];
	        pathu.push_back(u);
	    }
	    pathv.push_back(v);
	    while(v != r)
	    {
	        v = R[v];
	        pathv.push_back(v);
	    }
	    int i = 1;
	    while(i <= pathu.size() && i <= pathv.size() && pathu[pathu.size()-i] == pathv[pathv.size()-i]) i++;
	    int res;
	    if(i > pathu.size()) res = MST[ make_pair( pathv[pathv.size()-i] , pathv[pathv.size()-(i-1)] ) ];
	    else if(i > pathv.size()) res = MST[ make_pair( pathu[pathu.size()-i] , pathu[pathu.size()-(i-1)] ) ];
	    else res = max( MST[ make_pair( pathu[pathu.size()-i] , pathu[pathu.size()-(i-1)] ) ],
	                    MST[ make_pair( pathv[pathv.size()-i] , pathv[pathv.size()-(i-1)] ) ]);
	    pathu.clear();
	    pathv.clear();
	    return res;
	}
};

struct SegTree
{
	int time;
	int seg[2 * MAX][2];
	SegTree()
	{
	    for(int i = 0; i < 2 * MAX; i++)
	        seg[i][0] = seg[i][1] = 0;
	    time = 1;
	}
	void insert2(int v, int l, int r, int p, int a, int b)
	{
	    if(a >= r || b <= l)
	        return;
	    if(l <= a && b <= r)
	        seg[p][0] = v, seg[p][1] = time;
	    else
	    {
	        int m = (a + b) / 2;
	        insert2(v, l, r, p * 2, a, m);
	        insert2(v, l, r, p * 2 + 1, m, b);
	    }
	}
	void insert(int v, int l, int r)
	{
	    insert2(v, l, r, 1, 0, MAX);
	    time++;
	}
	int lookup(int i)
	{
	    int val = 0;
	    int latest = 0;
	    for(int p = MAX + i; p > 0; p /= 2)
	    {
	    	if(seg[p][1] > latest)
	    	{
	    		val = seg[p][0];
	    		latest = seg[p][1];
	    	}
	    }
	    return val;
	}
};

struct Tree
{
	vector<int> G[MAX];
	int G2[MAX];
	bool is_root[MAX];
	int dfs_times[MAX][2];
	int time;
	Tree()
	{
		time = 1;
	}
	void add_edge(int u, int v)
	{
		G[u].push_back(v);
		G2[v] = u;
	}
	void dfs(int v)
	{
		dfs_times[v][0] = time++;
		for(int i = 0; i < G[v].size(); i++)
			dfs(G[v][i]);
		dfs_times[v][1] = time++;
	}
	void get_dfs_times()
	{
		for(int i = 0; i < MAX; i++)
			if(is_root[i])
				dfs(i);
	}
};

SegTree segtree;
MaxDistTree maxtree;
Tree tree;

bool compare_by_dfs_in(int u, int v)
{
	return tree.dfs_times[u][0] < tree.dfs_times[v][0];
}

int M;
bool used[MAX];
int cycle[MAX]; // [v] is in cycle ?
int cycle_first[MAX]; // first edge in cycle
int cycle_cut[MAX]; // edge cut in cycle
int cycle_next = 1;
map<int, int> cycle_components;

int Q;
vector<int> True, False;

int main()
{
	for(int i = 0; i < MAX; i++)
	{
		used[i] = false;
		tree.is_root[i] = true;
		cycle[i] = -1;
	}
	cin >> M;
	for(int i = 1; i <= M; i++)
	{
		int a, b;
		cin >> a >> b;
		used[a] = used[b] = true;
		if(maxtree.Find(a) == maxtree.Find(b))
		{
			for(int v = a; v != b; v = tree.G2[v]) cycle[v] = cycle_next;
			cycle[b] = cycle_next;
			cycle_first[cycle_next] = b;
			cycle_cut[cycle_next] = i;
			cycle_next++;
		}
		else
		{
			tree.is_root[b] = false;
			tree.add_edge(a, b);
			maxtree.add_edge(a, b, i);
		}
	}
	tree.get_dfs_times();
	cin >> Q;
	for(int q = 0; q < Q; q++)
	{
		int first = INF;

		int nt, nf;
		cin >> nt;
		for(int i = 0; i < nt; i++)
		{
			int v;
			cin >> v;
			if(!used[v]) continue;
			True.push_back(v);
			//cout << cycle[v] << ' ' << maxtree.Find(v)<<endl;
			if(cycle[v] != -1) cycle_components[maxtree.Find(v)] = cycle[v];
		}
		cin >> nf;
		for(int i = 0; i < nf; i++)
		{
			int v;
			cin >> v;
			if(!used[v]) continue;
			False.push_back(v);
		}

		sort(True.begin(), True.end(), compare_by_dfs_in);

		segtree.insert(-1, 0, MAX); // reset segtree
		for(int i = 0; i < True.size(); i++)
			segtree.insert(True[i], tree.dfs_times[True[i]][0], tree.dfs_times[True[i]][1]);
		for(int i = 0; i < False.size(); i++)
		{
			int v = False[i];
			int closest_true = segtree.lookup(tree.dfs_times[v][0]);
			//cout << "closest_true="<<closest_true<<endl;
			if(closest_true == -1)
			{
				int Rv = maxtree.Find(v);
				//cout<<maxtree.R[v] << ' '<<Rv << endl;;
				//cout << cycle_cut[cycle_components[Rv]] << ' ';
				if(cycle_components.find(Rv) != cycle_components.end())
					first = min(first, max(cycle_cut[cycle_components[Rv]], maxtree.max_edge(cycle_first[cycle_components[Rv]], v)));
			}
			//cout << "closest of " << False[i] << " is " << closest_true << endl;
			//if(closest_true != -1) cout << "mindist is " << maxtree.max_edge(False[i], closest_true) << endl;
			if(closest_true != -1) first = min(first, maxtree.max_edge(closest_true, v));
		}

		True.clear();
		False.clear();
		cycle_components.clear();

		cout << (first == INF ? -1 : first) << '\n';
	}
	return 0;
}
