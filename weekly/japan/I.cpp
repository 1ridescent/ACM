#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

int N, M;
ll A;

ll power[55];
map<ll, ll> num[55]; // num[len][mask]

void modadd(ll& a, ll v)
{
	a = (a + v) % mod;
}
void modsub(ll& a, ll v)
{
	a = (a - v) % mod;
	if(a < 0) a += mod;
}

void precompute()
{
	power[0] = 1;
	for(int i = 1; i <= 50; i++)
		power[i] = (power[i - 1] * A) % mod;
	for(int len = 1; len <= 50; len++)
	{
		num[len][0] = power[len];
		for(int overlap = 1; overlap < len; overlap++)
		{
			ll factor = 1;
			if(2 * overlap < len) factor = power[len - 2 * overlap];
			for(map<ll, ll>::iterator it = num[overlap].begin(); it != num[overlap].end(); it++)
			{
				ll mask = it->first, number = it->second;
				if(2 * overlap > len && !(mask & (1LL << (2 * overlap - len)))) continue;
				modadd(num[len][(1LL << overlap) | mask], number * factor);
			}
		}
		//if(num[len].size() <= 10) { for(map<ll, ll>::iterator it = num[len].begin(); it != num[len].end(); it++) cout << it->first << ':' << it->second << ' '; cout << endl; }
		for(map<ll, ll>::iterator it = num[len].end(); it != num[len].begin(); )
		{
			it--;
			ll mask = it->first, number = it->second;
			for(int i = len; i >= 1; i--)
				if(mask & (1LL << i))
				{
					mask ^= (1LL << i);
					modsub(num[len][mask], number);
				}
		}
		//cout << len << ' ' << num[len][0] << ' ' << num[len].size() << endl;
		//if(num[len].size() <= 10) { for(map<ll, ll>::iterator it = num[len].begin(); it != num[len].end(); it++) cout << it->first << ':' << it->second << ' '; cout << endl; }
	}
}

ll dp[405][205][2]; // dp[pos][freq][end of word?]

int main()
{
	cin >> N >> M >> A;
	precompute();
	ll total = 0;
	for(map<ll, ll>::iterator it = num[M].begin(); it != num[M].end(); it++)
	{
		ll mask = it->first, number = it->second;
		if(number == 0) continue;
		vector<int> overlaps;
		overlaps.push_back(0);
		for(int i = 1; i <= M; i++)
			if(mask & (1LL << i))
				overlaps.push_back(i);
		int max_freq = N / (M - overlaps.back());
		for(int i = 0; i <= N; i++)
			for(int f = 0; f <= max_freq; f++)
				for(int b = 0; b < 2; b++)
					dp[i][f][b] = 0;
		dp[0][0][0] = 1;
		for(int i = 0; i < N; i++)
			for(int f = 0; f <= max_freq; f++)
			{
				if(dp[i][f][0])
				{
					modadd(dp[i + 1][f][0], dp[i][f][0] * A);
					modadd(dp[i + M][f + 1][1], dp[i][f][0]);
				}
				if(dp[i][f][1])
				{
					modadd(dp[i + 1][f][0], dp[i][f][1] * A);
					for(int j = 0; j < overlaps.size(); j++)
					{
						int k = overlaps[j];
						modadd(dp[i + M - k][f + 1][1], dp[i][f][1]);
					}
				}
			}
		ll res = 0;
		for(int f = 1; f <= max_freq; f++)
		{
			ll val = dp[N][f][0] + dp[N][f][1];
			//cout << f << ' ' << val << endl;
			if(f % 2) modadd(res, val);
			else modsub(res, val);
		}
		//cout << "mask = " << mask << ", number = " << number << ", res = " << res << endl;
		modadd(total, res * number);
	}
	cout << total << endl;
}
