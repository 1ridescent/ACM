#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ll;
const ll mod = 1000000009;
const int MAX = (1 << 19);

void init(ll C[2][2], ll a, ll b, ll c, ll d)
{
	C[0][0] = a, C[0][1] = b, C[1][0] = c, C[1][1] = d;
}
void add(ll A[2][2], ll B[2][2], ll C[2][2])
{
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			C[i][j] = (A[i][j] + B[i][j]) % mod;
}
void sub(ll A[2][2], ll B[2][2], ll C[2][2])
{
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			C[i][j] = (A[i][j] - B[i][j] + mod) % mod;
}
void mult(ll A[2][2], ll B[2][2], ll C[2][2])
{
	memset(C, 0, sizeof(C));
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			for(int k = 0; k < 2; k++)
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
}
void print(ll A[2][2])
{
	for(int i = 0; i < 2; i++)
	{
		cout << A[i][0] << ' ' << A[i][1] << '\n';
	}
}
void identity(ll C[2][2])
{
	init(C, 1, 0, 0, 1);
}

ll fib[MAX + 10][2][2];
ll inv[MAX + 10][2][2];
ll suff_fib[MAX + 10][2][2];
void precompute()
{
	ll f[2][2], finv[2][2];
	init(f, 1, 1, 1, 0);
	init(finv, 0, 1, 1, mod - 1);
	identity(fib[0]);
	identity(inv[0]);
	for(int i = 1; i <= MAX + 9; i++)
	{
		mult(fib[i - 1], f, fib[i]);
		mult(inv[i - 1], finv, inv[i]);
	}
	for(int i = MAX + 7; i >= 0; i--)
		add(suff_fib[i + 1], fib[i], suff_fib[i]);
}





ll dot(ll a[2], ll* v)
{
	return (a[0] * v[0] + a[1] * v[1]) % mod;
}
#define LC(p) ((p) * 2)
#define RC(p) ((p) * 2 + 1)
struct data
{
	ll m[2][2];
	ll val;
	ll delta[2];
};
data seg[2 * MAX];
void setup(int p, int a, int b)
{
	sub(suff_fib[a], suff_fib[b], seg[p].m);
	if(p < MAX)
	{
		int m = (a + b) / 2;
		setup(LC(p), a, m);
		setup(RC(p), m, b);
	}
}
void propagate_down(int p)
{
	if(p < MAX)
	{
		for(int i = 0; i < 2; i++)
		{
			seg[LC(p)].delta[i] = (seg[LC(p)].delta[i] + seg[p].delta[i]) % mod;
			seg[RC(p)].delta[i] = (seg[RC(p)].delta[i] + seg[p].delta[i]) % mod;
		}
	}
	seg[p].val = (seg[p].val + dot(seg[p].m[0], seg[p].delta)) % mod;
	for(int i = 0; i < 2; i++)
		seg[p].delta[i] = 0;
}
void propagate_up(int p)
{
	propagate_down(LC(p));
	propagate_down(RC(p));
	seg[p].val = (seg[LC(p)].val + seg[RC(p)].val) % mod;
}
void insert2(ll* v, int l, int r, int p, int a, int b)
{
	if(a >= r || b <= l) return;
	if(l <= a && b <= r)
	{
		for(int i = 0; i < 2; i++)
			seg[p].delta[i] = (seg[p].delta[i] + v[i]) % mod;
		return;
	}
	propagate_down(p);
	int m = (a + b) / 2;
	insert2(v, l, r, LC(p), a, m);
	insert2(v, l, r, RC(p), m, b);
	propagate_up(p);
}
void insert(int l, int r)
{
	ll s[2] = {1, 0};
	ll v[2];
	for(int i = 0; i < 2; i++)
		v[i] = dot(inv[l][i], s);
	insert2(v, l, r + 1, 1, 0, MAX);
}
ll lookup2(int l, int r, int p, int a, int b)
{
	if(a >= r || b <= l) return 0;
	propagate_down(p);
	if(l <= a && b <= r)
	{
		//printf("a=%d b=%d v=%d\n",a,b,(int)(seg[p].val));
		return seg[p].val;
	}
	int m = (a + b) / 2;
	return (lookup2(l, r, LC(p), a, m) + lookup2(l, r, RC(p), m, b)) % mod;
}
ll lookup(int l, int r)
{
	//printf("query %d %d:\n",l,r);
	return lookup2(l, r + 1, 1, 0, MAX);
}

int N, M;
ll A[MAX];

int main()
{
	precompute();
	setup(1, 0, MAX);
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= N; i++)
	{
		int x;
		scanf("%d", &x);
		A[i] = (A[i - 1] + x) % mod;
	}
	while(M--)
	{
		int t, l, r;
		scanf("%d %d %d", &t, &l, &r);
		if(t == 1) insert(l, r);
		else printf("%d\n", (int)((lookup(l, r) + A[r] - A[l - 1] + mod) % mod));
	}
}
