#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = (1 << 20);

struct SegTree
{
	ll val[2 * MAX];
	int cnt[2 * MAX];
	SegTree()
	{
		memset(val, 0, sizeof(val));
		memset(cnt, 0, sizeof(cnt));
	}
	void insert(int v, int i)
	{
		//printf("inserting v = %d, i = %d\n", v, i);
		for(i += MAX; i > 0; i /= 2)
			val[i] += v, cnt[i]++;
	}
	void erase(int i)
	{
		int v = val[i + MAX];
		for(i += MAX; i > 0; i /= 2)
			val[i] -= v, cnt[i]--;
	}
	ll lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return val[p];
		int m = (a + b) / 2;
		return lookup2(l, r, p * 2, a, m) + lookup2(l, r, p * 2 + 1, m, b);
	}
	ll lookup(int l, int r)
	{
		return lookup2(l, r + 1, 1, 0, MAX);
	}
	int count2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return cnt[p];
		int m = (a + b) / 2;
		return count2(l, r, p * 2, a, m) + count2(l, r, p * 2 + 1, m, b);
	}
	int count(int l, int r)
	{
		return count2(l, r + 1, 1, 0, MAX);
	}
	int rank(int k)
	{
		//printf("rank %d = ", k);
		int p;
		for(p = 1; p < MAX; )
		{
			if(cnt[2 * p] < k)
			{
				k -= cnt[2 * p];
				p = 2 * p + 1;
			}
			else
			{
				p = 2 * p;
			}
		}
		//printf("%d\n", p - MAX);
		return p - MAX;
	}
	void print()
	{
		for(int i = 0; i < 10; i++) printf("%d:%d ", (int)val[i + MAX], cnt[i + MAX]);
		printf("\n");
	}
};

ll gcd(ll a, ll b)
{
	if(b == 0) return a;
	return gcd(b, a % b);
}

int K;
ll L, D;
vector<ll> A[MAX];
vector<pair<int, pair<int, int> > > order;
vector<int> id[MAX];

SegTree seg;
set<pair<int, int> > cur;
int ind[MAX][2];
void insert(int k, int i)
{
	seg.insert(A[k][i], id[k][i]);
	cur.insert(make_pair(-A[k][i], id[k][i]));
}
void erase(int k, int i)
{
	seg.erase(id[k][i]);
	cur.erase(make_pair(-A[k][i], id[k][i]));
}

ll best_q, best_n, best_d;
void compare(ll q, ll n, ll d)
{
	if(q < best_q) return;
	if(q > best_q || n * (best_d / D) > best_n * (d / D))
		best_q = q, best_n = n, best_d = d;
}
void process(ll pref, int cnt, int p)
{
	ll num = seg.count(1, p);
	ll add = seg.lookup(1, p);
	ll alpha_n = L - num * D;
	ll alpha_d = cnt * D;
	//printf("pref = %d, num = %d, add = %d, a_n = %d, a_d = %d\n", (int)pref, (int)num, (int)add, (int)alpha_n, (int)alpha_d);
	if(alpha_n > alpha_d)
	{
		compare(pref + add, 0, D);
	}
	else
	{
		long double v = ((long double)L - (long double)num * D) / ((long double)cnt * D) * pref + add;
		if(v > best_q + (long double)best_n / best_d)
		{
			best_q = (ll)v;
			best_n = ((L - num * D) * pref + add * cnt * D) - ((ll)v) * cnt * D;
			best_d = cnt * D;
		}
		/*ll q = (ll)(add + ((long double)L * pref) / (cnt * D) - ((long double)num * pref) / cnt);
		ll n1 = (L * pref) % (cnt * D);
		ll n2 = (num * pref) % cnt;
		//printf("q = %d, n1 = %d, n2 = %d\n", (int)q, (int)n1, (int)n2);
		n2 *= D;
		if(n1 < n2)
		{
			n1 += cnt * D;
			q--;
		}
		compare(q, n1 - n2, cnt * D);*/
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> K >> L >> D;
	for(int k = 1; k <= K; k++)
	{
		int n;
		cin >> n;
		while(n--)
		{
			ll x;
			cin >> x;
			A[k].push_back(x);
		}
		sort(A[k].begin(), A[k].end(), greater<ll>());
		for(int i = 0; i < A[k].size(); i++)
			order.push_back(make_pair(-A[k][i], make_pair(k, i)));

		id[k] = vector<int>(A[k].size());
	}

	sort(order.begin(), order.end());
	for(int i = 0; i < order.size(); i++)
	{
		int k = order[i].second.first, ii = order[i].second.second;
		id[k][ii] = i + 1;
		ind[i + 1][0] = k, ind[i + 1][1] = ii;
	}

	for(int k = 1; k <= K; k++)
		for(int i = 0; i < A[k].size(); i++)
			insert(k, i);

	best_q = 0, best_n = 0, best_d = D;
	for(int k = 1; k <= K; k++)
	{
		for(int i = 0; i < A[k].size(); i++)
			erase(k, i);
		//seg.print();

		ll pref = 0;
		for(int i = 0; i < A[k].size(); i++)
		{
			//printf("===== k = %d, i = %d, A[k][i] = %d =====\n", k, i, A[k][i]);
			pref += A[k][i];
			int cnt = i + 1;
			process(pref, cnt, seg.rank(L / D - cnt));
			int l = seg.rank(L / D - cnt + 1), r = seg.rank(L / D);

			set<pair<int, int> >::iterator it = cur.lower_bound(make_pair(-(pref / cnt), -1));
			int p;
			if(it != cur.begin())
			{
				it--;
				p = it->second;
			}
			else p = 0;
			//printf("find %d/%d: k = %d, i = %d, id = %d, p = %d\n", (int)pref, cnt, ind[p][0], ind[p][1], p);
			if(p < l) p = l;
			if(p > r) p = r;
			process(pref, cnt, p);
		}

		for(int i = 0; i < A[k].size(); i++)
			insert(k, i);
	}

	ll g = gcd(best_n, best_d);
	best_n /= g, best_d /= g;

	if(best_d == 1) cout << best_q << '\n';
	else cout << best_q << " + " << best_n << '/' << best_d << '\n';
	return 0;
}
