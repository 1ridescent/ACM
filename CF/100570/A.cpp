#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long ll;
#define MOD(x) ((x) % 1000000007)

vector<int> primes;
int powers[61][17];
bool exceeds[61][61];

ll power[61][7];

void precompute()
{
	for(int i = 1; i <= 60; i++)
	{
		power[i][0] = 1;
		for(int j = 1; j <= 6; j++)
			power[i][j] = power[i][j - 1] * i;
	}
	for(int p = 2; p <= 60; p++)
	{
		bool isprime = true;
		for(int i = 2; i < p; i++)
			if(p % i == 0) isprime = false;
		if(isprime) primes.push_back(p);
	}
	for(int i = 1; i <= 60; i++)
	{
		for(int k = 0; k < primes.size(); k++)
		{
			int n = i;
			int p = primes[k];
			powers[i][k] = 0;
			while(n % p == 0)
				n /= p, powers[i][k]++;
		}
	}
	for(int i = 1; i <= 60; i++)
		for(int j = 1; j <= 60; j++)
		{
			exceeds[i][j] = false;
			for(int k = 0; k < primes.size(); k++)
			{
				if(powers[i][k] > powers[j][k])
					exceeds[i][j] = true;
			}
		}
}

int N, Q;

double log_best[20005];
ll best[20005];

vector<pair<int, int> > stk;

int main()
{
	precompute();
	cin >> N >> Q;
	for(int i = 0; i < 20005; i++) log_best[i] = 1e9;
	for(int j = 1; j <= N; j++)
	{
		int x;
		cin >> x;
		for(int i = stk.size() - 1; i >= 0; i--)
			if(!exceeds[stk[i].first][x])
				stk.erase(stk.begin() + i);
		stk.push_back(make_pair(x, j));
		int cur[17];
		memset(cur, 0, sizeof(cur));
		for(int i = stk.size() - 1; i >= 0; i--)
		{
			int len = j - (i == 0 ? 0 : stk[i - 1].second);
			for(int k = 0; k < primes.size(); k++)
				cur[k] = max(cur[k], powers[stk[i].first][k]);
			double log_val = 0;
			for(int k = 0; k < primes.size(); k++)
				log_val += cur[k] * log(primes[k]);
			if(log_val < log_best[len])
			{
				log_best[len] = log_val;
				best[len] = 1;
				for(int k = 0; k < primes.size(); k++)
				{
					best[len] = MOD(best[len] * power[primes[k]][cur[k]]);
				}
			}
		}
	}
	for(int l = N - 1; l >= 1; l--)
	{
		if(log_best[l + 1] < log_best[l])
		{
			log_best[l] = log_best[l + 1];
			best[l] = best[l + 1];
		}
	}
	while(Q--)
	{
		int l;
		cin >> l;
		cout << best[l] << '\n';
	}
}
