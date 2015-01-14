#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main()
{
	ll N, M, K;
	cin >> N >> M >> K;
	ll best = 0;
	for(ll n = 0; n <= K; n++)
	{
		if(N / (n + 1) == N / (n + 1011)) n = min(n + 1000, K);
		ll m = K - n;
		best = max(best, (N / (n + 1)) * (M / (m + 1)));
	}
	if(best == 0) best = -1;
	cout << best;
}
