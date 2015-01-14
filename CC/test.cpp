#include <iostream>

using namespace std;

typedef unsigned long long ll;

ll P = 24LL * (1LL << 27) + 1;

ll power(ll b, ll e)
{
	ll res = 1;
	while(e > 0)
	{
		if(e % 2 == 1) res = (res * b) % P;
		b = (b * b) % P;
		e /= 2;
	}
	return res;
}

int main()
{
	ll N, K;
	cin >> N >> K;
	cout << power(N, K);
}
