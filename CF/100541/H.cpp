#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e17;

vector<int> primes;
bool is_prime[2000005];
void pre()
{
	memset(is_prime, -1, sizeof(is_prime));
	for(int i = 2; i <= 2000000; i++)
	{
		if(is_prime[i]) primes.push_back(i);
		for(int j = i + i; j <= 2000000; j += i)
			is_prime[j] = false;
	}
}

vector<pair<ll, int> > F;
vector<ll> factors;
void dfs(ll v, int i)
{
	if(i == F.size()) factors.push_back(v);
	else
		for(int j = 0; j <= F[i].second; j++)
		{
			dfs(v, i + 1);
			v *= F[i].first;
		}
}
void factor(ll x)
{
	F.clear();
	for(int i = 0; i < primes.size(); i++)
	{
		if(x % primes[i] == 0)
		{
			int n = 0;
			while(x % primes[i] == 0)
			{
				n++;
				x /= primes[i];
			}
			F.push_back(make_pair(primes[i], n));
		}
	}
	if(x > 1) F.push_back(make_pair(x, 1));
	factors.clear();
	dfs(1, 0);
	sort(factors.begin(), factors.end());
	//for(int i=0;i<factors.size();i++)cout<<factors[i]<<' ';cout<<endl;
}

ll N, M, K;
inline bool check_row(ll r1, ll r2)
{
	return (r1 % 2 == 0 && r2 % 2 == 0 && 0 <= r1 && r2 < 2 * N);
}
inline bool check_col(ll c1, ll c2)
{
	return (c1 % 2 == 0 && c2 % 2 == 0 && 0 <= c1 && c2 < 2 * M);
}

bool Try(ll dr, ll dc)
{
	ll s = dr * dc;
	if(K % s != 0) return false;
	return true;
}

int main()
{
	pre();
	//ll x;cin>>x;factor(x);return 0;
	int t;
	cin >> t;
	while(t--)
	{
		cin >> N >> M >> K;
		factor(2 * K);
		ll best = inf;
int cnt=0;		for(int i = 0; i < factors.size(); i++)
			for(int j = 0; factors[i] * factors[j] <= K; j++)
				cnt++;
cout<<cnt<<endl;

		cout << (best == inf ? -1 : best) << '\n';
	}
}
