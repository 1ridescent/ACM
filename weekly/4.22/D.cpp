#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 23);
struct SegTree
{
	int seg[2 * MAX];
	int delta[2 * MAX];
	void init()
	{
		memset(seg, 0, sizeof(seg));
		memset(delta, 0, sizeof(delta));
	}
	void propagate_up(int p)
	{
		seg[p] = max(seg[p * 2], seg[p * 2 + 1]);
	}
	void propagate_down(int p)
	{
		if(p >= MAX) return;
		seg[p * 2] += delta[p];
		delta[p * 2] += delta[p];
		seg[p * 2 + 1] += delta[p];
		delta[p * 2 + 1] += delta[p];
		delta[p] = 0;
	}
	int lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return seg[p];
		propagate_down(p);
		int m = (a + b) / 2;
		return max(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r + 1, 1, 0, MAX);
	}
	void insert2(int v, int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return;
		if(l <= a && b <= r)
		{
			seg[p] += v;
			delta[p] += v;
		}
		else
		{
			propagate_down(p);
			int m = (a + b) / 2;
			insert2(v, l, r, p * 2, a, m);
			insert2(v, l, r, p * 2 + 1, m, b);
			propagate_up(p);
		}
	}
	void insert(int v, int l, int r)
	{
		//printf("insert %d in [%d, %d]\n", v, l, r);
		insert2(v, l, r + 1, 1, 0, MAX);
	}
};

typedef pair<int, int> point;
#define x first
#define y second

point transform(point p)
{
	return point(p.x + p.y, p.x - p.y + 1000005);
}
int N, K;
vector<pair<pair<int, int>, int> > X[MAX];
SegTree S;

int main()
{
	cin >> N >> K;
	for(int i = 0; i < N; i++)
	{
		int g;
		cin >> g;
		point p;
		cin >> p.x >> p.y;
		p = transform(p);
		X[p.x].push_back(make_pair(make_pair(p.y, min(MAX - 1, p.y + 2 * K)), g));
		X[min(MAX - 1, p.x + 2 * K + 1)].push_back(make_pair(make_pair(p.y, min(MAX - 1, p.y + 2 * K)), -g));
	}
	S.init();
	int best = 0;
	for(int x = 0; x < MAX; x++)
	{
		if(X[x].empty()) continue;
		for(int i = 0; i < X[x].size(); i++)
			S.insert(X[x][i].second, X[x][i].first.first, X[x][i].first.second);
		best = max(best, S.lookup(0, MAX - 1));
	}
	cout << best << endl;
}
