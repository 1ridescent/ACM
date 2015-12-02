#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e18;

int N;
ll init_cost;
vector<pair<ll, int> > costs;
vector<ll> one_one;

ll Try(int k)
{
	ll total = 0, cost = init_cost;
	for(int i = 0; i < costs.size(); i++)
	{
		if(costs[i].second != -1 && costs[i].second < k) continue;
		cost += costs[i].first;
		total += cost;
	}
	return total;
}

int mane()
{
	string from, to;
	cin >> from >> to;
	init_cost = 0;
	for(int i = 0; i < N; i++)
	{
		ll c;
		cin >> c;
		if(from[i] == '1') init_cost += c;
		if(from[i] == '1' && to[i] == '1') one_one.push_back(c);
		else if(from[i] == '1') costs.push_back(make_pair(-c, -1));
		else if(to[i] == '1') costs.push_back(make_pair(c, -1));
	}
	sort(one_one.begin(), one_one.end());
	for(int i = 0; i < one_one.size(); i++)
	{
		costs.push_back(make_pair(-one_one[i], i));
		costs.push_back(make_pair(one_one[i], i));
	}
	sort(costs.begin(), costs.end());
	ll ans = inf;
	for(int k = 0; k <= one_one.size(); k++)
		ans = min(ans, Try(k));
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	for(int i = 1; ; i++)
	{
		costs.clear();
		one_one.clear();
		cin >> N;
		if(N == 0) break;
		cout << "Case " << i << ": ";
		mane();
	}
}
