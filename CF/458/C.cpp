#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAX = (1 << 17);

struct RankSegTree
{
	int seg[2 * MAX + 10];
	RankSegTree()
	{
		memset(seg, 0, sizeof(seg));
	}
	void insert(int v, int i)
	{
		for(i += MAX; i > 0; i /= 2) seg[i] += v;
	}
	int rank(int k)
	{
		int p;
		for(p = 1; p < MAX; )
		{
			//cout << 2*p << ' ' << seg[2*p] << endl;
			if(seg[2 * p] < k)
			{
				k -= seg[2 * p];
				p = 2 * p + 1;
			}
			else
			{
				p = 2 * p;
			}
		}
		return p - MAX;
	}
};

struct BIT
{
	ll bit[MAX + 10];
	BIT()
	{
		memset(bit, 0, sizeof(bit));
	}
	void insert(ll v, int i)
	{
		i += 10;
		for(; i < MAX; i += i & -i) bit[i] += v;
	}
	ll lookup(int i)
	{

		i += 10;
		ll res = 0;
		for(; i > 0; i -= i & -i) res += bit[i];
		return res;
	}
};

RankSegTree seg;
BIT bit;

int N;

struct voter
{
	int cand;
	ll cost;
	int i;
};
voter voters[MAX + 10];
bool cmp_voter(voter a, voter b)
{
	return a.cost < b.cost;
}

struct candidate
{
	int i;
	vector< voter >* c;
};
candidate cand[MAX + 10];

bool cmp_cand(candidate a, candidate b)
{
	return a.c->size() > b.c->size();
}

int main()
{
	ios::sync_with_stdio(0);
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> voters[i].cand >> voters[i].cost;
	}
	sort(voters + 1, voters + 1 + N, cmp_voter);
	for(int i = 1; i <= N; i++)
	{
		voters[i].i = i;
		seg.insert(1, i);
		bit.insert(voters[i].cost, i);
	}
	
	for(int i = 0; i <= 100000; i++)
	{
		cand[i].i = i;
		cand[i].c = new vector<voter>;
	}
	for(int i = N; i >= 1; i--)
	{
		cand[voters[i].cand].c->push_back(voters[i]); // decr order
	}
	sort(cand + 1, cand + 100001, cmp_cand);
	//for(int i = 1; i <= 5; i++) cout << cand[i].i;

	ll res = (1LL << 60);

	ll required_cost = 0;
	ll required_cnt = 0;
	int next_p = 1;
	for(int win = N; win >= 1; win--)
	{
		while(cand[next_p].c->size() >= win) next_p++;
		for(int c = 1; c < next_p; c++)
		{
			int i = cand[c].c->back().i;
			required_cost += voters[i].cost;
			required_cnt++;
			seg.insert(-1, i);
			bit.insert(-voters[i].cost, i);
			cand[c].c->pop_back();
		}
		ll rem = win - required_cnt;
		ll total = required_cost;
		if(rem > 0) total += bit.lookup(seg.rank(rem));

		//cout << win << ": " << required_cnt << ' ' << required_cost << ' ' << total << endl;

		res = min(res, total);
	}
	cout << res;
}
