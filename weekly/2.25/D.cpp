#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 18);
const int INF = 1e8;

struct MaxSegTree
{
	int seg[2 * MAX];
	void init(int v)
	{
		for(int i = 0; i < 2 * MAX; i++) seg[i] = v;
	}
	void insert2(int v, int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return;
		if(l <= a && b <= r) seg[p] = max(seg[p], v);
		else
		{
			int m = (a + b) / 2;
			insert2(v, l, r, p * 2, a, m);
			insert2(v, l, r, p * 2 + 1, m, b);
		}
	}
	void insert(int v, int l, int r)
	{
		insert2(v, l, r + 1, 1, 0, MAX);
	}
	int lookup(int i)
	{
		int res = -INF;
		for(i += MAX; i > 0; i /= 2) res = max(res, seg[i]);
		return res;
	}
};
struct MinSegTree
{
	MaxSegTree S;
	void init(int v)
	{
		S.init(-v);
	}
	void insert(int v, int l, int r)
	{
		S.insert(-v, l, r);
	}
	int lookup(int i)
	{
		return -S.lookup(i);
	}
};
struct MaxSegTree2
{
	int seg[2 * MAX];
	void init(int v)
	{
		for(int i = 0; i < 2 * MAX; i++) seg[i] = v;
	}
	void insert(int v, int i)
	{
		for(i += MAX; i > 0; i /= 2) seg[i] = max(seg[i], v);
	}
	int lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return -INF;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return max(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r + 1, 1, 0, MAX);
	}
};

int N, M;
pair<int, int> S[MAX];
MaxSegTree extend;
MinSegTree within;
MaxSegTree2 dp;

int main()
{
	cin >> N >> M;
	extend.init(0);
	for(int i = 0; i <= N + 1; i++)
		extend.insert(i, i, i);
	within.init(N + 1);
	for(int i = 0; i < M; i++)
	{
		int l, r;
		cin >> l >> r;
		S[i] = make_pair(l, r);
		extend.insert(r, l, r);
		within.insert(r, 0, l - 1);
	}
	//for(int i = 1; i <= N; i++) cout << within.lookup(i) << ' ';
	dp.init(-INF);
	dp.insert(0, N + 1);
	for(int i = N; i >= 0; i--) // add cow here?
	{
		int l = extend.lookup(i) + 1, r = within.lookup(i);
		//printf("dp[%d]: l=%d r=%d v=%d\n", i, l, r, 1 + dp.lookup(l, r));
		int v = dp.lookup(l, r);
		if(i == 0) cout << (v < 0 ? -1 : v) << endl;
		dp.insert(1 + v, i);
	}
}
