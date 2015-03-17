#include <iostream>
#include <algorithm>
#include <set>
#include <cstdlib>

using namespace std;

typedef long long ll;

int N;
ll K;
pair<int, int> P[100005];
set<pair<int, int> > S;

ll ans = 0;
void update(ll x)
{
	//cout << "updating " << x << endl;
	if(ans != 0)
	{
		cout << "-1\n";
		exit(0);
	}
	ans = x;
}

int main()
{
	cin >> N >> K;
	for(int i = 0; i < N; i++) cin >> P[i].first >> P[i].second;
	sort(P, P + N);
	int l = 0;
	for(int r = 0; r < N; r++)
	{
		//cout << "p = " << P[r].first << ' ' << P[r].second << endl;
		while(P[r].first - P[l].first >= K)
		{
			S.erase(make_pair(P[l].second, P[l].first));
			l++;
		}
		//cout << "l = " << l << endl;
		set<pair<int, int> >::iterator it = S.lower_bound(make_pair(P[r].second, -1));
		if(it != S.end())
		{
			//cout << "y = " << it->first << endl;
			if(abs(it->first - P[r].second) < K)
			{
				update((K - abs(it->second - P[r].first)) * (K - abs(it->first - P[r].second)));
			}
		}
		if(it != S.begin())
		{
			it--;
			//cout << "y = " << it->first << endl;
			if(abs(it->first - P[r].second) < K)
			{
				update((K - abs(it->second - P[r].first)) * (K - abs(it->first - P[r].second)));
			}
		}
		S.insert(make_pair(P[r].second, P[r].first));
	}
	cout << ans << endl;
}
