#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e17;

int N, K;
ll A[5050];
map<ll, int> S;

int main()
{
	cin >> N >> K;
	for(int i = 0; i < N; i++)
	{
		cin >> A[i];
		for(int k = 0; k <= K; k++)
		{
			ll v = A[i] * k;
			if(S.count(v))
				S[v] = min(S[v], k);
			else S[v] = k;
		}
	}
	int Q;
	cin >> Q;
	while(Q--)
	{
		ll x;
		cin >> x;
		ll best = inf;
		for(int i = 0; i < N; i++)
		{
			for(int k = 0; k <= K; k++)
			{
				ll v = A[i] * k;
				if(S.count(x - v)) best = min(best, (ll)k + S[x - v]);
			}
		}
		cout << (best > K ? -1 : best) << '\n';
	}
}
