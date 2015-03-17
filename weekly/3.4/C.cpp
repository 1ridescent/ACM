#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 19);

typedef long long ll;
int N;
ll G, B, D;
pair<ll, ll> M[MAX];

struct BIT
{
	ll bit[MAX];
	void insert(ll v, int i)
	{
		for(; i < MAX; i += i & -i) bit[i] += v;
	}
	ll lookup(int i)
	{
		ll r = 0;
		for(; i > 0; i -= i & -i) r += bit[i];
		return r;
	}
	ll add_seg(ll v, int l, int r)
	{
		insert(v, l);
		insert(-v, r + 1);
	}
};

BIT cost, Left;
int S0 = 10, S1 = 10;

int main()
{
	cin >> N >> G >> B >> D;
	for(int i = 0; i < N; i++) cin >> M[i].first >> M[i].second;
	M[N] = make_pair(D, 0);
	sort(M, M + N + 1);
	ll cur = 0, vol = B;
	ll total = 0;
	for(int m = 0; cur < D; m++)
	{
		ll next = M[m].first;
		ll dist = next - cur - vol;
		if(dist <= 0) vol -= (next - cur);
		while(dist > 0)
		{
			vol = 0;
			if(S0 == S1)
			{
				cout << "-1\n";
				return 0;
			}
			ll c = cost.lookup(S0), v = Left.lookup(S0);
			if(v <= 0)
			{
				S0++;
				continue;
			}
			v = min(v, dist);
			//cout << "add " << v << " at cost " << c << endl;
			total += c * v;
			dist -= v;
			//cout << "left = " << Left.lookup(S0) << endl;
			Left.add_seg(-v, S0, S1 - 1);
			//cout << "left = " << Left.lookup(S0) << endl;
		}
		cur = next;
		ll c = M[m].second;
		while(S0 != S1 && cost.lookup(S1 - 1) >= c)
		{
			ll v = cost.lookup(S1 - 1);
			//cout << "top is " << v << endl;
			cost.add_seg(-v, S1 - 1, S1 - 1);
			Left.add_seg(-Left.lookup(S1 - 1), S1 - 1, S1 - 1);
			S1--;
		}
		cost.add_seg(c, S1, S1);
		//cout<<"left: ";	for(int i = S0; i < S1; i++) cout << Left.lookup(i) << ' '; cout << endl;

		Left.add_seg(G - vol, S1, S1);
		S1++;
		//cout<<"left: ";	for(int i = S0; i < S1; i++) cout << Left.lookup(i) << ' '; cout << endl;
	}
	cout << total << endl;
}
