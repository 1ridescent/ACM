#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 19);
const int INF = 1e9;
struct MinSegTree
{
	int seg[2 * MAX];
	void init()
	{
		for(int i = 0; i < 2 * MAX; i++) seg[i] = INF;
	}
	void insert(int v, int i)
	{
		for(i += MAX; i > 0; i /= 2) seg[i] = min(seg[i], v);
	}
	int lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return INF;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return min(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r + 1, 1, 0, MAX);
	}
};

MinSegTree S;
vector<int> insert[500005];
vector<pair<int, int> > query[500005];
int ans[500005];

int N, M;
map<int, int> prev;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
	{
		int a;
		cin >> a;
		if(prev.count(a))
			insert[i].push_back(prev[a]);
		prev[a] = i;
	}
	for(int i = 1; i <= M; i++)
	{
		int l, r;
		cin >> l >> r;
		query[r].push_back(make_pair(l, i));
	}
	S.init();
	for(int t = 1; t <= N; t++)
	{
		for(int i = 0; i < insert[t].size(); i++)
		{
			int s = insert[t][i];
			S.insert(t - s, s);
		}
		for(int i = 0; i < query[t].size(); i++)
		{
			int s = query[t][i].first;
			ans[query[t][i].second] = S.lookup(s, t);
		}
	}
	for(int i = 1; i <= M; i++)
		cout << (ans[i] == INF ? -1 : ans[i]) << '\n';
}
