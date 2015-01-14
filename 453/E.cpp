#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <cassert>

using namespace std;

typedef long long ll;
const int MAX = (1 << 17);
const int INF = 1000000005;

class SegTree
{
public:
	ll seg[2 * MAX];
	void init()
	{
		memset(seg, 0, sizeof(seg));
	}
	void insert(int v, int i)
	{
		for(i += MAX; i > 0; i /= 2) seg[i] += v;
	}
	ll lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return lookup2(l, r, p * 2, a, m) + lookup2(l, r, p * 2 + 1, m, b);
	}
	ll lookup(int l, int r) // [l, r]
	{
		r++;
		return lookup2(l, r, 1, 0, MAX);
	}
};

struct pony
{
	ll s, m, r;
};
int N;
pony P[MAX];

pair<int, int> time_maxed[MAX];
SegTree maxed;
SegTree rate;

struct query
{
	int l, r, t;
	int i;
	ll v;
};
bool query_cmp(query a, query b)
{
	return a.t < b.t;
}

vector<query> Q;
void process_queries()
{
	for(int i = 1; i <= N; i++) time_maxed[i] = make_pair(P[i].r == 0 ? INF : (P[i].m + P[i].r - 1) / P[i].r, i);
	sort(time_maxed + 1, time_maxed + 1 + N);
	int cur_time_i = 1;

	maxed.init();
	rate.init();
	for(int i = 1; i <= N; i++) rate.insert(P[i].r, i);
	
	sort(Q.begin(), Q.end(), query_cmp);
	for(int qi = 0; qi < Q.size(); qi++)
	{
		query& q = Q[qi];
		if(q.t < 0)
		{
			assert(q.l == q.r);
			int i = q.l, t = q.t + INF;
			q.v = min(P[i].s + t * P[i].r, P[i].m);
			continue;
		}
		while(cur_time_i <= N && q.t >= time_maxed[cur_time_i].first)
		{
			int i = time_maxed[cur_time_i].second;
			maxed.insert(P[i].m, i);
			rate.insert(-P[i].r, i);
			cur_time_i++;
		}
		q.v = maxed.lookup(q.l, q.r) + q.t * rate.lookup(q.l, q.r);
	}
}

map<pair<int, char>, int> segments; // (index, l/r) -> time

ll res[MAX];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> P[i].s >> P[i].m >> P[i].r;

	for(int i = 1; i <= N; i++)
	{
		segments[make_pair(i, 'l')] = INF; // indicates initial
		segments[make_pair(i, 'r')] = INF;
	}

	int M;
	cin >> M;
	for(int m = 0; m < M; m++)
	{
		int t, l, r;
		cin >> t >> l >> r;

		map<pair<int, char>, int>::iterator it;
		// left endpoint
		it = segments.lower_bound(make_pair(l, 'l'));
		if(it->first.second == 'r') // split segment
		{
			segments[make_pair(l - 1, 'r')] = it->second;
			segments[make_pair(l, 'l')] = it->second;
		}

		// right endpoint
		it = --segments.upper_bound(make_pair(r, 'r'));
		if(it->first.second == 'l') // split segment
		{
			segments[make_pair(r + 1, 'l')] = it->second;
			segments[make_pair(r, 'r')] = it->second;
		}

		// sweep middle
		for(it = segments.lower_bound(make_pair(l, 'l')); it != segments.upper_bound(make_pair(r, 'r')); )
		{
			int prev_t = it->second;
			assert(it->first.second == 'l');
			int prev_l = it->first.first;
			it++;
			assert(it->first.second == 'r');
			int prev_r = it->first.first;
			it++;

			query q;
			q.l = prev_l, q.r = prev_r, q.t = t - prev_t, q.i = m;
			Q.push_back(q);

			segments.erase(make_pair(prev_l, 'l'));
			segments.erase(make_pair(prev_r, 'r'));
		}

		segments[make_pair(l, 'l')] = t;
		segments[make_pair(r, 'r')] = t;
	}

	process_queries();
	memset(res, 0, sizeof(res));
	for(int i = 0; i < Q.size(); i++) res[Q[i].i] += Q[i].v;

	for(int i = 0; i < M; i++) cout << res[i] << '\n';
}
