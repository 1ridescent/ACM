#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int N;
		ll W;
		cin >> N >> W;
		ll A[105];
		for(int i = 0; i < N; i++) cin >> A[i];
		ll best = 0;
		for(int s = 0; s < N; s++)
			for(int t = s + 1; t < N; t++)
			{
				ll x = W / A[s];
				best = max(best, x * (A[t] - A[s]));
			}
		cout << best << '\n';
	}
}
