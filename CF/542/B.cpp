#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = (1 << 20);
const ll INF = 1e11;
struct BIT
{
	pair<ll, ll> bit[MAX]; // (pos, score)
	void insert(pair<ll, ll> v, int i)
	{
		for(; i < MAX; i += i & -i)
		{
			bit[i].first += v.first;
			bit[i].second += v.second;
		}
	}
	pair<ll, ll> lookup(int i)
	{
		pair<ll, ll> res(0, 0);
		for(; i > 0; i -= i & -i)
		{
			res.first += bit[i].first;
			res.second += bit[i].second;
		}
		return res;
	}
	int find(int score)
	{
		int low = 0, high = MAX;
		while(low + 1 < high)
		{
			int mid = (low + high) / 2;
			if(lookup(mid).second < score) low = mid;
			else high = mid;
		}
		return high;
	}
};

BIT bit;

ll N, R;
set<ll> X;
map<ll, vector<ll> > L;
map<ll, int> ids;

int main()
{
	cin >> N >> R;
	R *= 2;
	for(int i = 0; i < N; i++)
	{
		ll l, r;
		cin >> l >> r;
		l *= 2;
		r *= 2;
		r++;
		if(r < 0) continue;
		l = max(l, 0LL);
		X.insert(l);
		X.insert(r);
		L[r].push_back(l);
	}
	X.insert(-INF);
	X.insert(INF);
	int next_id = 4;
	ids[-INF] = next_id;
	bit.insert(make_pair(0, 1), next_id);
	next_id++;

	set<ll>::iterator it = X.begin();
	while(true)
	{
		// [l, r)
		ll l = *it;
		it++;
		if(it == X.end()) break;
		ll r = *it;
		for(int i = 0; i < L[l].size(); i++)
		{
			int id = (--ids.lower_bound(L[l][i]))->second;
			bit.insert(make_pair(0, 1), L[l][i] + 1);
			bit.insert(make_pair(0, -1), next_id);
		}
		int score = bit.lookup(next_id - 1).second;
		int prev_id = bit.find(score);
		if(prev_id > 0)
		{
			ll prev_x = bit.lookup(prev_id).second;
			if(prev_x + R < r)
			{
				int next_x = max(prev_x + R, l);
				ids[next_x] = next_id;
				bit.insert(make_pair(next_x, 0), next_id);
				next_id++;
			}
		}
	}
	cout << bit.lookup(next_id).second - 1 << endl;
}
