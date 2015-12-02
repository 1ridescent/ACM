#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1000000007;
ll base[2] = {13, 37};
ll key[256][2];

ll power(ll b, int e)
{
	if(e == 0) return 1;
	ll r = power(b, e / 2);
	r = (r * r) % mod;
	if(e % 2 == 1) r = (r * b) % mod;
	return r;
}
ll inv(ll x)
{
	return power(x, mod - 2);
}

void setup()
{
	for(int i = 0; i < 256; i++)
	{
		key[i][0] = rand() % mod;
		key[i][1] = rand() % mod;
	}
}

struct Hash
{
	ll mult[2], add[2], invmult[2];
	unordered_set<ll> H;
	Hash()
	{
		for(int i = 0; i < 2; i++)
			mult[i] = 1, add[i] = 0, invmult[i] = 1;
	}
	ll actual(ll x)
	{
		ll a = (x >> 32);
		a = (mult[0] * a + add[0]) % mod;
		ll b = (int)x;
		b = (mult[1] * b + add[1]) % mod;
		return ((a << 32) | b);
	}
	ll convert(ll x)
	{
		ll a = (x >> 32);
		a = (invmult[0] * (a - add[0] + mod)) % mod;
		ll b = (int)x;
		b = (invmult[1] * (b - add[1] + mod)) % mod;
		return ((a << 32) | b);
	}
	ll update(ll m[2], ll a[2])
	{
		for(int i = 0; i < 2; i++)
		{
			mult[i] = (mult[i] * m[i]) % mod;
			add[i] = (add[i] * m[i] + a[i]) % mod;
			invmult[i] = inv(mult[i]);
		}
	}
	void print()
	{
		for(ll x : H) cout << actual(x) << ' ';
		cout << endl;
	}
};

Hash* collapse(Hash* a, Hash* b)
{
	if(a->H.size() < b->H.size()) return collapse(b, a);
	for(ll x : b->H) a->H.insert(a->convert(b->actual(x)));
	return a;
}

int N;
int C[300005];
char A[300005];
vector<int> G[300005];
Hash* H[300005];

int size[300005];

void dfs(int u, int p)
{
	//cout << "at " << u << endl;
	for(int v : G[u])
	{
		//cout << u << " -> " << v << endl;
		if(v != p) dfs(v, u);
	}
	H[u] = new Hash();
	for(int v : G[u]) if(v != p) H[u] = collapse(H[u], H[v]);
	H[u]->H.insert(H[u]->convert(0));
	H[u]->update(base, key[A[u]]);
	size[u] = H[u]->H.size();
	//cout << u << " has size " << size[u] << endl;
	//H[u]->print();
}

int main()
{
	ios::sync_with_stdio(false);
	setup();
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> C[i];
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 1; i < N; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, -1);
	int best = -1, num;
	for(int i = 1; i <= N; i++)
	{
		int v = size[i] + C[i];
		if(v > best) best = v, num = 1;
		else if(v == best) num++;
	}
	cout << best << '\n' << num << endl;
}
