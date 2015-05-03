#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <map>

using namespace std;

typedef long long ll;
const ll inf = 1e12;

int N;
ll A, B;

vector<pair<ll, bool> > cows;
ll res = 0;

void add(ll l, ll r, bool b)
{
	l = max(l, A);
	r = min(r, B);
	if(l <= r && b) res += (r - l + 1);
}

int main()
{
	cin >> N >> A >> B;
	for(int i = 0; i < N; i++)
	{
		string s;
		cin >> s;
		ll w;
		cin >> w;
		cows.push_back(make_pair(w, (s == "S")));
	}
	cows.push_back(make_pair(-inf, false));
	cows.push_back(make_pair(inf, false));
	sort(cows.begin(), cows.end());
	for(int i = 1; i < cows.size() - 1; i++)
		add(cows[i].first, cows[i].first, cows[i].second);
	for(int i = 1; i < cows.size(); i++)
	{
		ll l = cows[i - 1].first, r = cows[i].first;
		bool a = cows[i - 1].second, b = cows[i].second;
		l++;
		r--;
		if(l > r) continue;
		if((l + r) % 2 == 0)
		{
			ll m = (l + r) / 2;
			add(l, m - 1, a);
			add(m, m, a || b);
			add(m + 1, r, b);
		}
		else
		{
			ll m1 = (l + r - 1) / 2, m2 = (l + r + 1) / 2;
			add(l, m1, a);
			add(m2, r, b);
		}
	}
	cout << res << endl;
}
