#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int MOD;
ll power(ll b, ll e)
{
	if(e == 0) return (1 % MOD);
	ll res = power(b, e / 2);
	res = (res * res) % MOD;
	if(e % 2) res = (res * b) % MOD;
	return res;
}

vector<int> primes;


int factor[155][44];

bool is_prime(int x)
{
	for(int i = 2; i < x; i++)
		if(x % i == 0)
			return false;
	return true;
}
void pre()
{
	for(int i = 2; i < 150; i++)
		if(is_prime(i))
			primes.push_back(i);
	for(int x = 1; x <= 150; x++)
		for(int i = 0; i < primes.size(); i++)
		{
			int x2 = x, p = primes[i];
			while(x2 % p == 0)
				x2 /= p, factor[x][i]++;
		}
}






const int MAX = (1 << 17);
struct SegTree
{
	ll seg[2 * MAX][35];
	ll delta[2 * MAX][35];
	void init()
	{
		memset(seg, 0, sizeof(seg));
		memset(delta, 0, sizeof(delta));
	}
	ll array[35];
	void lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return;
		if(l <= a && b <= r)
		{
			for(int i = 0; i < 35; i++)
				array[i] += seg[p][i];
			return;
		}
		if(p < MAX) {
			int l = b - a;
			for(int i = 0; i < 35; i++)
			{
				seg[p * 2][i] += (l / 2) * delta[p][i];
				delta[p * 2][i] += delta[p][i];
				seg[p * 2 + 1][i] += (l / 2) * delta[p][i];
				delta[p * 2 + 1][i] += delta[p][i];
				delta[p][i] = 0;
			}}
		int m = (a + b) / 2;
		lookup2(l, r, p * 2, a, m);
		lookup2(l, r, p * 2 + 1, m, b);
	}
	ll lookup(int l, int r, int mod)
	{
		memset(array, 0, sizeof(array));
		lookup2(l, r + 1, 1, 0, MAX);
		ll res = 1;
		MOD = mod;
		for(int i = 0; i < 35; i++)
			if(array[i])
				res = (res * power(primes[i], array[i])) % mod;
		return res;
	}
	void insert2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return;
		if(p < MAX) {
			int l = b - a;
			for(int i = 0; i < 35; i++)
			{
				seg[p * 2][i] += (l / 2) * delta[p][i];
				delta[p * 2][i] += delta[p][i];
				seg[p * 2 + 1][i] += (l / 2) * delta[p][i];
				delta[p * 2 + 1][i] += delta[p][i];
				delta[p][i] = 0;
			} }
		if(l <= a && b <= r)
		{
			for(int i = 0; i < 35; i++)
			{
				seg[p][i] += (b - a) * array[i];
				delta[p][i] += array[i];
			}
		}
		else
		{
			int m = (a + b) / 2;
			insert2(l, r, p * 2, a, m);
			insert2(l, r, p * 2 + 1, m, b);

			if(p >= MAX) return;
			for(int i = 0; i < 35; i++)
				seg[p][i] = seg[p * 2][i] + seg[p * 2 + 1][i];


		}
	}
	void insert(int x, int l, int r, int s)
	{
		memset(array, 0, sizeof(array));
		for(int i = 0; i < 35; i++)
			array[i] += s * factor[x][i];
		insert2(l, r + 1, 1, 0, MAX);
	}
};

SegTree S;

int main2()
{
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	S.init();
	while(M--)
	{
		int t;
		cin >> t;
		if(t == 0)
		{
			int l, r, p;
			cin >> l >> r >> p;
			if(l <= r) cout << S.lookup(l, r, p) << '\n';
			else cout << (S.lookup(l, N, p) * S.lookup(1, r, p)) % p << '\n';
		}
		else
		{
			int s = (t == 1 ? 1 : -1);
			int l, r, x;
			cin >> l >> r >> x;
			if(l <= r)
				S.insert(x, l, r, s);
			else
			{
				S.insert(x, l, N, s);
				S.insert(x, 1, r, s);
			}
		}
	}
}

int main()
{
	pre();
	int t;
	cin >> t;
	while(t--) main2();

	/*while(true)
	{
		char c;
		cin >> c;
		if(c == 'i')
		{
			int v, l, r;
			cin >> v >> l >> r;
			S.insert(v, l, r);
		}
		else
		{
			int l, r;
			cin >> l >> r;
			cout << S.lookup(l, r) << '\n';
		}
	}*/
}
