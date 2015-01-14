#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

class data
{
public:
	int length;
	bool all_ones;
	int pref_ones;
	int suff_ones;
	int max_ones;
	data() { }
	data(bool b)
	{
		length = 1;
		all_ones = b;
		pref_ones = suff_ones = max_ones = b;
	}
};

const int MAX = (1 << 17);

data seg[2 * MAX];

data f(data& l, data& r)
{
	data p;
	p.length = l.length + r.length;
	p.all_ones = (l.all_ones && r.all_ones);
	p.pref_ones = (l.all_ones ? l.length + r.pref_ones : l.pref_ones);
	p.suff_ones = (r.all_ones ? l.suff_ones + r.length : r.suff_ones);
	p.max_ones = max(max(l.max_ones, r.max_ones), l.suff_ones + r.pref_ones);
	return p;
}
void propagate_up(int p)
{
	if(p >= MAX) return;
	seg[p] = f(seg[p * 2], seg[p * 2 + 1]);
}
void init()
{
	for(int i = 0; i < MAX; i++)
		seg[i + MAX] = data(false);
	for(int p = MAX - 1; p > 0; p--)
		propagate_up(p);
}
void insert(bool b, int i)
{
	seg[i + MAX] = data(b);
	for(int p = i + MAX; p > 0; p /= 2)
		propagate_up(p);
}
data lookup2(int l, int r, int p, int a, int b)
{
	if(a >= r || b <= l) return 0;
	if(l <= a && b <= r) return seg[p];
	int m = (a + b) / 2;
	data l2 = lookup2(l, r, p * 2, a, m);
	data r2 = lookup2(l, r, p * 2 + 1, m, b);
	return f(l2, r2);
}
int lookup(int l, int r)
{
	return lookup2(l, r + 1, 1, 0, MAX).max_ones;
}


int N;
int A[100005];
vector< pair<int, int> > heights;

struct query
{
	int l, r, w;
};
query Q[MAX];

int ans[MAX];

void solve(vector<int>& V, int l, int r) // [l, r)
{
	if(l >= r) return;
	int m = (l + r) / 2;
	int h = heights[m].first;

	for(int i = m; i < r; i++) insert(true, heights[i].second);
	vector<int> low, high;
	for(int i = 0; i < V.size(); i++)
	{
		if(lookup(Q[V[i]].l, Q[V[i]].r) < Q[V[i]].w) // too high
			low.push_back(V[i]);
		else
		{
			ans[V[i]] = h;
			high.push_back(V[i]);
		}
	}

	solve(low, l, m);
	for(int i = m; i < r; i++) insert(false, heights[i].second);
	solve(high, m + 1, r);
}

int main()
{
	ios::sync_with_stdio(false);

	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> A[i];
		heights.push_back(make_pair(A[i], i));
	}
	sort(heights.begin(), heights.end());

	init();

	int M;
	cin >> M;
	vector<int> V;
	for(int i = 0; i < M; i++)
	{
		cin >> Q[i].l >> Q[i].r >> Q[i].w;
		V.push_back(i);
	}

	solve(V, 0, heights.size());

	for(int i = 0; i < M; i++)
		cout << ans[i] << '\n';
}
