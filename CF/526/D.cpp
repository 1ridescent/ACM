#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = 1000100;
const ll base = 2, invbase = 500000004, mod = 1000000007;

int N;
char S[MAX];

struct Hash
{
	ll key[256];
	ll power[MAX];
	ll inv[MAX];
	ll hash[MAX];
	void init()
	{
		for(int i = 0; i < 256; i++)
			key[i] = rand() % mod;
		power[0] = inv[0] = 1;
		for(int i = 1; i < N; i++)
		{
			power[i] = (power[i - 1] * base) % mod;
			inv[i] = (inv[i - 1] * invbase) % mod;
		}
		hash[0] = (power[0] * key[S[0]]) % mod;
		for(int i = 1; i < N; i++)
			hash[i] = (hash[i - 1] + power[i] * key[S[i]]) % mod;
	}
	ll get(ll start, ll len)
	{
		return (inv[start] * (hash[start + len - 1] - (start == 0 ? 0LL : hash[start - 1]) + mod)) % mod;
	}
};

Hash hash[1];
int lcp(int s1, int s2)
{
	int low = 0, high = N - max(s1, s2) + 1;
	while(low + 1 < high)
	{
		int mid = (low + high) / 2;
		if(hash[0].get(s1, mid) == hash[0].get(s2, mid))// && hash[1].get(s1, mid) == hash[1].get(s2, mid))
			low = mid;
		else high = mid;
	}
	return low;
}

int delta[MAX];
void insert(int l, int r)
{
	//cout << "insert " << l << ' ' << r << endl;
	delta[l]++, delta[r + 1]--;
}
void collect()
{
	for(int i = 1; i < MAX; i++)
		delta[i] += delta[i - 1];
}

ll K;
char ans[MAX];

int main()
{
	srand(time(0));
	cin >> N >> K;
	scanf("%s", S);
	hash[0].init();
	//hash[1].init();
	for(ll len = 1; len <= N; len++)
	{
		ll val = lcp(0, len);
		//cout << len << ' ' << val << endl;
		if(val >= (K - 1) * len)
			insert(K * len, min((K + 1) * len, val + len));
	}
	collect();
	for(int i = 1; i <= N; i++) ans[i] = (delta[i] > 0 ? '1' : '0');
	puts(ans + 1);
}
