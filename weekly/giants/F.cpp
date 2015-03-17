#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

#define LOG(x) (63 - __builtin_clzll(x))

vector<ll> crates[60];

int N;
ll S;

map<ll, ll> cur;
vector<ll> temp;
bool test(ll area)
{
	for(int s = 59; s >= 0; s--)
	{
		if(area & (1LL << s)) cur[0] += (1LL << s);
		for(int i = 0; i < crates[s].size(); i++)
		{
			ll h_new = crates[s][i];
			if(cur.empty()) break;
			map<ll, ll>::iterator h_old = cur.begin();
			if(h_old->first >= h_new) break;
			temp.push_back(h_new);
			h_old->second -= (1LL << s);
			if(h_old->second == 0) cur.erase(h_old);
		}
		for(int i = 0; i < temp.size(); i++)
			cur[temp[i]] += (1LL << s);
		temp.clear();
	}
	ll total = 0;
	for(map<ll, ll>::iterator it = cur.begin(); it != cur.end(); it++)
		total += it->first * it->second;
	cur.clear();
	return (total >= S);
}

int main()
{
	cin >> N >> S;
	for(int i = 0; i < N; i++)
	{
		ll a, h;
		cin >> a >> h;
		crates[LOG(a)].push_back(h);
	}
	for(int i = 0; i < 60; i++)
		sort(crates[i].begin(), crates[i].end(), greater<ll>());
	ll low = 0, high = (1LL << 60) - 1;
	while(low + 1 < high)
	{
		ll mid = (low + high) / 2;
		if(test(mid)) high = mid;
		else low = mid;
	}
	cout << high << endl;
}
