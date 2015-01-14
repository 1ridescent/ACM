#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> primes;

bool isprime[100005];
void sieve()
{
	memset(isprime, 0xFF, sizeof(isprime));
	for(int i = 2; i <= 100003; i++)
	{
		if(isprime[i])
		{
			primes.push_back(i);
			for(int j = 2 * i; j <= 100003; j += i)
			{
				isprime[j] = false;
			}
		}
	}
}

bool used[100005];
vector< pair<int, int> > res;

int main()
{
	ios::sync_with_stdio(false);
	sieve();//cout<<primes.size();
	int N;
	cin >> N;
	memset(used, 0, sizeof(used));
	for(int i = primes.size() - 1; i >= 0; i--)
	{
		int p = primes[i];
		if(N / p <= 1) continue;
		int cur = -1;
		for(int x = p; x <= N; x += p)
		{
			if(x == 2 * p) continue;
			if(used[x]) continue;
			if(cur == -1) cur = x;
			else
			{
				res.push_back(make_pair(cur, x));
				used[cur] = used[x] = true;
				cur = -1;
			}
		}
		if(cur != -1)
		{
			res.push_back(make_pair(cur, 2 * p));
			used[cur] = used[2 * p] = true;
		}
	}
	cout << res.size() << '\n';
	for(int i = 0; i < res.size(); i++) cout << res[i].first << ' ' << res[i].second << '\n';
}
