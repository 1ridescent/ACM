#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll mod1 = 1000000007;
const ll mod2 = 23456789;
#define MOD1(x) ((x + 1000LL * mod1) % mod1)
#define MOD2(x) ((x + 1000LL * mod2) % mod2)

const int MAX = (1 << 17);
const int OFFSET = 1111;

struct BIT
{
	ll arr1[MAX];
	ll bit1[MAX];
	ll arr2[MAX];
	ll bit2[MAX];
	void init()
	{
		memset(arr1, 0, sizeof(arr1));
		memset(bit1, 0, sizeof(bit1));
		memset(arr2, 0, sizeof(arr2));
		memset(bit2, 0, sizeof(bit2));
	}
	void insert1(ll v, int i)
	{
		i += OFFSET;
		int i0 = i;
		for(; i < MAX; i += i & -i)
			bit1[i] = MOD1(bit1[i] + (v - arr1[i0]));
		arr1[i0] = v;
	}
	ll lookup12(int i)
	{
		i += OFFSET;
		ll res = 0;
		for(; i > 0; i -= i & -i)
			res = MOD1(res + bit1[i]);
		return res;
	}
	ll lookup1(int l, int r)
	{
		return MOD1(lookup12(r) - lookup12(l - 1));
	}
	void insert2(ll v, int i)
	{
		i += OFFSET;
		int i0 = i;
		for(; i < MAX; i += i & -i)
			bit2[i] = MOD2(bit2[i] + (v - arr2[i0]));
		arr2[i0] = v;
	}
	ll lookup22(int i)
	{
		i += OFFSET;
		ll res = 0;
		for(; i > 0; i -= i & -i)
			res = MOD2(res + bit2[i]);
		return res;
	}
	ll lookup2(int l, int r)
	{
		return MOD2(lookup22(r) - lookup22(l - 1));
	}
};

ll powmod1(ll b, ll e)
{
	if(e == 0) return 1;
	ll res = powmod1(b, e / 2);
	res = MOD1(res * res);
	if(e & 1) res = MOD1(res * b);
	return res;
}
ll invmod1(ll b)
{
	return powmod1(b, mod1 - 2);
}
ll powmod2(ll b, ll e)
{
	if(e == 0) return 1;
	ll res = powmod2(b, e / 2);
	res = MOD2(res * res);
	if(e & 1) res = MOD2(res * b);
	return res;
}
ll invmod2(ll b)
{
	return powmod2(b, mod2 - 2);
}

ll hash[256];

ll pow1[MAX], inv1[MAX];
ll pow2[MAX], inv2[MAX];

int N;
BIT L, R;
string S;

int main()
{
	ios::sync_with_stdio(false);
	srand(time(0));
	for(int i = 0; i < 256; i++)
		hash[i] = 100000000 + MOD1(rand());
	for(int i = 0; i < MAX; i++)
	{
		pow1[i] = powmod1(2, i);
		inv1[i] = invmod1(pow1[i]);
		pow2[i] = powmod2(2, i);
		inv2[i] = invmod2(pow2[i]);
	}

	cin >> S;
	L.init();
	R.init();
	N = S.size();
	for(int i = 0; i < N; i++)
	{
		L.insert1(MOD1(hash[S[i]] * pow1[i]), i);
		R.insert1(MOD1(hash[S[i]] * pow1[N - i]), i);
		L.insert2(MOD2(hash[S[i]] * pow2[i]), i);
		R.insert2(MOD2(hash[S[i]] * pow2[N - i]), i);
	}

	int Q;
	cin >> Q;
	while(Q--)
	{
		int t;
		cin >> t;
		if(t == 1)
		{
			int p;
			char x;
			cin >> p >> x;
			p--;
			L.insert1(MOD1(hash[x] * pow1[p]), p);
			R.insert1(MOD1(hash[x] * pow1[N - p]), p);
			L.insert2(MOD2(hash[x] * pow2[p]), p);
			R.insert2(MOD2(hash[x] * pow2[N - p]), p);
		}
		else if(t == 2)
		{
			int p;
			cin >> p;
			p--;
			int low = 1, high = min(p + 1, N - p) + 1;
			while(low + 1 < high)
			{
				int mid = (low + high) / 2;
				if(MOD1(L.lookup1(p, p + mid - 1) * inv1[p] - R.lookup1(p - mid + 1, p) * inv1[N - p]) == 0
						&&
				   MOD2(L.lookup2(p, p + mid - 1) * inv2[p] - R.lookup2(p - mid + 1, p) * inv2[N - p]) == 0)
					low = mid;
				else high = mid;
			}
			cout << 2 * low - 1 << '\n';
		}
		else if(t == 3)
		{
			int p;
			cin >> p;
			p--;
			int low = 0, high = min(p + 1, N - p - 1) + 1;
			while(low + 1 < high)
			{
				int mid = (low + high) / 2;
				if(MOD1(L.lookup1(p + 1, p + 1 + mid - 1) * inv1[p + 1] - R.lookup1(p - mid + 1, p) * inv1[N - p]) == 0
						&&
				   MOD2(L.lookup2(p + 1, p + 1 + mid - 1) * inv2[p + 1] - R.lookup2(p - mid + 1, p) * inv2[N - p]) == 0)
					low = mid;
				else high = mid;
			}
			cout << (low == 0 ? -1 : 2 * low) << '\n';
		}
	}
}
