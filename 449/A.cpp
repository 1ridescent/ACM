#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main()
{
	ll N, M, K;
	cin >> N >> M >> K;
	if(K > N + M - 2)
	{
		cout << "-1\n";
		return 0;
	}
	ll best = 0;
	if(K <= 1e7)
	{
		for(ll n = 0; n <= K; n++)
		{
			ll m = K - n;
			ll val = (N / (n + 1)) * (M / (m + 1));
			best = max(best, val);
		}
	}
	else
	{
		for(ll n = 0; n <= K; n++)
		{
			if(n < K - 111 && N / (n + 1) == N / (n + 111))
			{
				n += 100;
				continue;
			}
			ll m = K - n;
			
			ll val = (N / (n + 1)) * (M / (m + 1));
			best = max(best, val);
		}
		for(ll m = 0; m <= K; m++)
		{
			if(m < K - 111 && M / (m + 1) == M / (m + 111))
			{
				m += 100;
				continue;
			}
			ll n = K - m;
			
			ll val = (N / (n + 1)) * (M / (m + 1));
			best = max(best, val);
		}
		for(ll i = 1; i <= 1e7; i++)
		{
			ll n = N / i - 1;
			ll m = K - n;
			if(n < 0 || m < 0) continue;
			ll val = (N / (n + 1)) * (M / (m + 1));
			best = max(best, val);
			
		}
	}
	cout << best;
}
