#include <bits/stdc++.h>

using namespace std;

int N, D;

const int MAX = (1 << 21);
const int INF = (1 << 30);
class Tree
{
public:
	pair<int, int> seg[2*MAX];
	void insert(pair<int, int> v, int i)
	{
		for(int p = i+MAX; p > 0; p /= 2) seg[p] = min(seg[p], v);
	}
	pair<int, int> lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return make_pair(INF, INF);
		if(l <= a && b <= r) return seg[p];
		int m = (a+b)/2;
		return min(lookup2(l, r, p*2, a, m), lookup2(l, r, p*2+1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r, 1, 0, MAX).second;
	}
	vector<int> G[MAX];
	void init()
	{
		for(int i = 0; i < MAX; i++) G[i].clear();
	}
	int depth[MAX];
	int dfstime[MAX];
	int timestamp;
	void dfs(int v, int p, int d)
	{
		depth[v] = d;
		dfstime[v] = timestamp;
		insert(make_pair(d, v), timestamp);
		timestamp++;
		for(int i = 0; i < G[v].size(); i++)
		{
			int w = G[v][i];
			if(w == p) continue;
			dfs(w, v, d+1);
			insert(make_pair(d, v), timestamp);
			timestamp++;
		}
	}
	void get_dfstimes()
	{
		for(int i = 0; i < 2*MAX; i++) seg[i] = make_pair(INF, INF);
		timestamp = 1;
		dfs(1, -1, 1);
	}
	int lca(int u, int v)
	{
		//cout << dfstime[u] << ' ' << dfstime[v] << endl;
		if(u == v) return u;
		return lookup(min(dfstime[u], dfstime[v]), max(dfstime[u], dfstime[v]));
	}
};

Tree T;
pair<int, int> S[MAX];
int M[MAX];
pair<int, int> order[MAX];
set<pair<int, int> > cur;

int mane()
{
	T.init();
	cin >> N >> D;
	{
		long long s, a, c, r;
		cin >> s >> a >> c >> r;
		for(int i = 0; i < N; i++)
		{
			S[i] = make_pair(s, i);
			s = (s * a + c) % r;
		}
		cin >> s >> a >> c >> r;
		for(int i = 0; i < N; i++)
		{
			M[i] = s;
			s = (s * a + c) % r;
			T.G[M[i] % i].push_back(i);
		}
	}
	setup_dfs(0, -1, 0);
	cur.clear();
	for(int i = 0; i < N; i++) order[i] = make_pair(T.dfstime[i], i);
	sort(S, S + N);
	for(int i = N - 1; i >= 0; i--)
	{

	}
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cout << "Case #" << t << ": ";
		mane();
	}
}
