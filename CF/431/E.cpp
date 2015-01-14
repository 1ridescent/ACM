#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;

int N, Q;
pair<ll, int> cur[100100];

struct query
{
	ll t, p, x, v, id;
};
query qs[100100];
vector< pair<ll, int> > vals;

const int MAX = (1 << 17);
struct SumSegTree
{
	ll seg[2 * MAX];
	void init()
	{
		memset(seg, 0, sizeof(seg));
	}
	void insert(ll v, int p)
	{
		for(p += MAX; p > 0; p /= 2)
		{
			seg[p] += v;
		}
	}
	ll lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return lookup2(l, r, p * 2, a, m) + lookup2(l, r, p * 2 + 1, m, b);
	}
	ll lookup(int l, int r)
	{
		return lookup2(l, r, 1, 0, MAX);
	}
}
SumSegTree sumtree;

const ll INF = (1LL << 60);
struct MinSegTree
{
	ll seg[2 * MAX];
	void init()
	{
		for(int i = 0; i < 2 * MAX; i++) seg[i] = INF;
	}
	void insert(ll v, int p)
	{
		for(p += MAX; p > 0; p /= 2)
		{
			seg[p] = min(seg[p], v);
		}
	}
	ll lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return INF;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return min(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
	}
	ll lookup(int l, int r)
	{
		return lookup2(l, r, 1, 0, MAX);
	}
};
MinSegTree mintree;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> Q;
	for(int i = 1; i <= N; i++)
	{
		cin >> cur[i].first;
		vals.push_back(make_pair(cur[i].first, -i));
	}
	for(int q = 0; q < Q; q++)
	{
		cin >> qs[q].t;
		if(qs[q].t == 1)
		{
			cin >> qs[q].p >> qs[q].x;
			vals.push_back(make_pair(qs[q].x, q));
		}
		else
		{
			cin >> qs[q].v;
		}
	}

	sort(vals.begin(), vals.end());

	for(int i = 0; i < vals.size(); i++)
	{
		if(vals[i].second < 0) cur[-vals[i].second].second = i;
		else qs[vals[i].second].id = i;
	}

	sumtree.init();
	mintree.init();
	for(int i = 1; i <= N; i++)
	{
		sumtree.insert(cur[i].first, cur[i].second);
		mintree.insert(cur[i].first, cur[i].second);
	}
	for(int q = 0; q < Q; q++)
	{
		if(qs[q].t == 1)
		{
			int p = qs[q].p;
			sumtree.insert(-cur[p].first, cur[p].second);
			mintree.insert(-cur[p].first, cur[p].second);
			cur[p] = make_pair(qs[q].x, qs[q].id);
			sumtree.insert(cur[p].first, cur[p].second);
			mintree.insert(cur[p].first, cur[p].second);
		}
		else
		{
			ll v = qs[q].v;
			int low = 0, high = MAX + 1;
			while(low + 1 < high)
			{
				int mid = (low + high) / 2;
				ll total = sumtree.lookup(0, mid + 1);
				if(total > v)
				{
					high = mid;
					continue;
				}
				ll all = total + v;
				ll num = mid + 1;

			}
		}
	}
}
