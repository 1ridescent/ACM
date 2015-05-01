#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e15;

int N;
pair<ll, ll> bales[100005];
map<pair<ll, char>, bool> field;

int main()
{
	freopen("trapped.in","r",stdin);freopen("trapped.out","w",stdout);
	cin >> N;
	for(int i = 0; i < N; i++) cin >> bales[i].first >> bales[i].second;
	sort(bales, bales + N);
	field[make_pair(-inf, 'o')] = field[make_pair(inf, 'c')] = true;
	ll sum = 0;
	for(int i = N - 1; i >= 0; i--)
	{
		ll s = bales[i].first, x = bales[i].second;
		auto high = field.upper_bound(make_pair(x, '.'));
		auto low = high;
		low--;
		//cout << s << ' ' << x << ' ' << low->first.first << ' ' << high->first.first << endl;
		if(!low->second)
		{
			assert(!high->second);
			field[make_pair(x, 'c')] = false;
			field[make_pair(x, 'o')] = false;
		}
		else
		{
			if(x - low->first.first <= s)
			{
				//cout << low->first.first << ' ' << x << endl;
				sum += x - low->first.first;
				low->second = field[make_pair(x, 'c')] = false;
			}
			else field[make_pair(x, 'c')] = true;
			if(high->first.first - x <= s)
			{
				//cout << x << ' ' << high->first.first << endl;
				sum += high->first.first - x;
				high->second = field[make_pair(x, 'o')] = false;
			}
			else field[make_pair(x, 'o')] = true;
		}
	}
	cout << sum << endl;
}
