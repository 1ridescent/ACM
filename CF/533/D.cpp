#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e14;

int N;
ll X[100005];
ll D[100005];

vector<int> alive;
vector<pair<int, ll> > reach; // (index, reach)

map<ll, ll> best_left, best_right; // position -> index

void fix_alive(int i)
{
	while(true)
	{
		if(alive.size() < 2) break;
		int j = alive[alive.size() - 1], k = alive[alive.size() - 2];
		//printf("i=%d j=%d k=%d %d >? %d\n",i,j,k,(int)abs(X[i]-X[k])/2,(int)D[j]);
		if(abs(X[i] - X[k]) / 2 > D[j])
			alive.pop_back();
		else break;
	}
}

ll Try(ll x)
{
	int l = (--best_left.upper_bound(x))->second;
	int r = (best_right.lower_bound(x))->second;
	//printf("%d: l=%d r=%d res=%d\n", (int)x, l, r, (int)abs(X[r]-X[l])/2);
	return abs(X[r] - X[l]) / 2;
}

int main()
{
	cin >> N;
	for(int i = 0; i <= N + 1; i++)
	{
		cin >> X[i];
		X[i] *= 2;
	}
	D[0] = D[N + 1] = inf;
	for(int i = 1; i <= N; i++)
	{
		cin >> D[i];
		D[i] *= 2;
	}
	alive.push_back(0);
	reach.push_back(make_pair(0, inf));
	best_left[0] = 0;
	for(int i = 1; i <= N + 1; i++)
	{
		while(reach.back().second <= X[i])
		{
			//printf("best_left[%d] = %d\n", (int)reach.back().second, reach.back().first);
			best_left[reach.back().second] = reach.back().first;
			reach.pop_back();
		}
		//printf("best_left[%d] = %d\n", X[i], reach.back().first);
		if(!best_left.count(X[i])) best_left[X[i]] = reach.back().first;
		//best_left[X[i]] = reach.back().first;
		fix_alive(i);
		ll add = 2 * D[i] - abs(X[i] - X[alive.back()]);
		if(add > 0)
		{
			while(reach.back().second <= X[i] + add)
				reach.pop_back();
			reach.push_back(make_pair(i, X[i] + add));
		}
		alive.push_back(i);
	}
	if(alive.size() >= 3)
	{
		//for(int i = 0; i < alive.size(); i++) cout << alive[i] << ' '; cout << endl;
		cout << "0\n";
		return 0;
	}
	alive.clear();
	reach.clear();
	alive.push_back(N + 1);
	reach.push_back(make_pair(N + 1, -inf));
	best_right[X[N + 1]] = N + 1;
	for(int i = N; i >= 0; i--)
	{
		while(reach.back().second >= X[i])
		{
			//printf("best_right[%d] = %d\n", (int)reach.back().second, reach.back().first);
			best_right[reach.back().second] = reach.back().first;
			reach.pop_back();
		}
		//printf("best_right[%d] = %d\n", (int)reach.back().second, reach.back().first);
		if(!best_right.count(X[i])) best_right[X[i]] = reach.back().first;
		//best_right[X[i]] = reach.back().first;
		fix_alive(i);
		ll add = 2 * D[i] - abs(X[i] - X[alive.back()]);
		if(add > 0)
		{
			while(reach.back().second >= X[i] - add)
				reach.pop_back();
			reach.push_back(make_pair(i, X[i] - add));
		}
		alive.push_back(i);
	}
	if(alive.size() >= 3)
	{
		cout << "0\n";
		return 0;
	}

	ll best = inf;
	for(map<ll, ll>::iterator it = best_left.begin(); it != best_left.end(); it++)
	{
		//cout << it->first << ' ' << it->second << endl;
		if(0 < it->first && it->first < X[N + 1])
			best = min(best, Try(it->first));
	}
	for(map<ll, ll>::iterator it = best_right.begin(); it != best_right.end(); it++)
		if(0 < it->first && it->first < X[N + 1])
			best = min(best, Try(it->first));
	cout << best / 2;
	if(best % 2) cout << ".5";
	cout << endl;
	//cout << best << endl;
}
