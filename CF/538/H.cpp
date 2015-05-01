#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 19);
struct SegTree
{
	int seg[2 * MAX];
	int num;
	void init()
	{
		memset(seg, 0, sizeof(seg));
		num = 0;
	}
	void insert2(int v, int l, int r, int p, int a, int b)
	{
		//printf("%d %d %d %d %d %d\n",v,l,r,p,a,b); if(!p) return;
		if(a >= r || b <= l) return;
		if(l <= a && b <= r) seg[p] += v;
		else
		{
			int m = (a + b) / 2;
			insert2(v, l, r, p * 2, a, m);
			insert2(v, l, r, p * 2 + 1, m, b);
			seg[p] = max(seg[p * 2], seg[p * 2 + 1]);
		}
	}
	void insert(int l, int r)
	{
		num++;
		insert2(1, l, r + 1, 1, 0, MAX);
	}
	void erase(int l, int r)
	{
		num--;
		insert2(-1, l, r + 1, 1, 0, MAX);
	}
	int find_first(int p = 1)
	{
		int v = num;
		if(seg[p] < v) return -1;
		if(p >= MAX) return p - MAX;
		if(seg[p * 2] >= v) return find_first(p * 2);
		return find_first(p * 2 + 1);
	}
	int find_last(int p = 1)
	{
		int v = num;
		if(seg[p] < v) return -1;
		if(p >= MAX) return p - MAX;
		if(seg[p * 2 + 1] >= v) return find_last(p * 2 + 1);
		return find_last(p * 2);
	}
};

void no()
{
	cout << "IMPOSSIBLE";
	exit(0);
}

int A, B;
int N, M;
int L[MAX], R[MAX];
vector<int> G[MAX];

int color[MAX];
int dfs_id[MAX];
vector<int> cur;
void two_color(int u, int c)
{
	//cout << u << ' ' << c << endl;
	color[u] = c;
	cur.push_back(u);
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(color[v] != -1)
		{
			if(color[v] == c) no();
		}
		else two_color(v, !c);
	}
}

const int inf = 2e9;
vector<pair<int, int> > segs;
vector<vector<int> > groups;
SegTree S;

map<int, int> id;
int val[MAX];
void add(int x)
{
	id[x - 1] = id[x] = id[x + 1] = -1;
}
void process()
{
	int next_id = 0;
	for(map<int, int>::iterator it = id.begin(); it != id.end(); it++)
	{
		next_id++;
		val[next_id] = it->first;
		it->second = next_id;
	}
}

bool inside[MAX];
vector<int> del[MAX], ins[MAX];

char ans[MAX];
void yes(int l, int r)
{
	printf("POSSIBLE\n%d %d\n", l, r);
	for(int i = 0; i < groups.size(); i++)
		for(int j = 0; j < groups[i].size(); j++)
			ans[groups[i][j]] = (inside[i] ? '2' : '1');
	printf("%s\n", ans + 1);
	exit(0);
}

int main()
{
	cin >> A >> B >> N >> M;
	for(int i = 1; i <= N; i++)
		cin >> L[i] >> R[i];
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	memset(color, -1, sizeof(color));
	int next_id = 0;
	for(int s = 1; s <= N; s++)
	{
		if(color[s] == -1)
		{
			two_color(s, 0);
			int low = -inf, high = inf;
			for(int i = 0; i < cur.size(); i++)
			{
				low = max(low, L[cur[i]]);
				high = min(high, R[cur[i]]);
			}
			if(low > high) no();
			segs.push_back(make_pair(low, high));
			groups.push_back(cur);
			cur.clear();
		}
	}//return 0;

	for(int i = 0; i < segs.size(); i++)
	{
		add(segs[i].first);
		add(segs[i].second);
	}
	process();
	for(int i = 0; i < segs.size(); i++)
	{
		del[id[segs[i].first]].push_back(i);
		ins[id[segs[i].second]].push_back(i);
	}

	S.init();
	for(int i = 0; i < segs.size(); i++)
	{
		inside[i] = true;
		S.insert(id[segs[i].first], id[segs[i].second]);
	}

	for(map<int, int>::iterator it = id.begin(); it != id.end(); it++)
	{
		int t = it->first, i = it->second;
		for(int j = 0; j < del[i].size(); j++)
		{
			int k = del[i][j];
			inside[k] = false;
			S.erase(id[segs[k].first], id[segs[k].second]);
		}
		int l = S.find_first(), r = S.find_last();
		if(l != -1 && r != -1)
		{
			l = val[l], r = val[r];
			if(A <= t + l && t + l <= B) yes(t, l);
			if(A <= t + r && t + r <= B) yes(t, r);
			if(t + l <= A && A <= t + r) yes(t, A - l);
		}
		for(int j = 0; j < ins[i].size(); j++)
		{
			int k = ins[i][j];
			inside[k] = true;
			S.insert(id[segs[k].first], id[segs[k].second]);
		}
	}
	no();
}
