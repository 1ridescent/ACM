#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll compute(ll S, ll K)
{
	ll score[105], when[105];
	memset(score, 0, sizeof(score));
	memset(when, 0, sizeof(when));
	ll res = 0;
	ll iter = 1;
	bool looped = false;
	while(iter <= K)
	{
		//cout << res << ' ' << iter << ' ' << S << endl;
		if(!looped && when[S])
		{
			ll period = iter - when[S];
			//cout << "period = " << period << endl;
			ll loops = (K - iter) / period;
			res += loops * (res - score[S]);
			iter += loops * period;
			looped = true;
		}
		else
		{
			score[S] = res;
			when[S] = iter;
			iter++;
			S *= 2;
			if(S >= 100)
			{
				res++;
				S -= 100;
			}
		}
	}
	return res * 100 + S;
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		ll N, K;
		cin >> N >> K;
		cout << (N - N % 100) + compute(N % 100, K) << endl;
	}
}
