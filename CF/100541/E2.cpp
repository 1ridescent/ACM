#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX = (1 << 17);
struct SegTree
{
	ll seg[2 * MAX];
	ll delta[2 * MAX];
	void init()
	{
		memset(seg, 0, sizeof(seg));
		memset(delta, 0, sizeof(delta));
	}
	void propagate_up(int p)
	{
		seg[p] = seg[p * 2] + seg[p * 2 + 1];
	}
	void propagate_down(int p, int a, int b)
	{
		if(p >= MAX) return;
		int l = b - a;
		seg[p * 2] += (l / 2) * delta[p];
		delta[p * 2] += delta[p];
		seg[p * 2 + 1] += (l / 2) * delta[p];
		delta[p * 2 + 1] += delta[p];
		delta[p] = 0;
	}
	ll lookup(int l, int r, int p = 1, int a = 0, int b = MAX)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return seg[p];
		propagate_down(p, a, b);
		int m = (a + b) / 2;
		return lookup(l, r, p * 2, a, m) + lookup(l, r, p * 2 + 1, m, b);
	}
	void insert(int v, int l, int r, int p = 1, int a = 0, int b = MAX)
	{
		if(a >= r || b <= l) return;
		propagate_down(p, a, b);
		if(l <= a && b <= r)
		{
			seg[p] += (b - a) * v;
			delta[p] += v;
		}
		else
		{
			int m = (a + b) / 2;
			insert(v, l, r, p * 2, a, m);
			insert(v, l, r, p * 2 + 1, m, b);
			propagate_up(p);
		}
	}
};

ll power(ll b, int e, ll p)
{
	if(e == 0) return (1 % p);
	ll res = power(b, e / 2, p);
	res = (res * res) % p;
	if(e % 2) res = (res * b) % p;
	return res;
}

vector<int> primes;

SegTree S[44];

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

int main2()
{
	int N, M;
	cin >> N >> M;
	for(int i = 0; i < primes.size(); i++)
		S[i].init();
	while(M--)
	{
		int t;
		cin >> t;
		if(t == 0)
		{
			int l, r, p;
			cin >> l >> r >> p;
			ll res = 1;
			for(int i = 0; i < primes.size(); i++)
				res = (res * power(primes[i], S[i].lookup(l, r + 1), p)) % p;
			cout << res << '\n';
		}
		else
		{
			int s = (t == 1 ? 1 : -1);
			int l, r, x;
			cin >> l >> r >> x;
			for(int i = 0; i < primes.size(); i++)
				if(factor[x][i])
					S[i].insert(s * factor[x][i], l, r + 1);
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
