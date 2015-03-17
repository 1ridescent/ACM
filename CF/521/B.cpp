#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000009;

ll M;
ll power[100005];

pair<int, int> P[100005];
map<pair<int, int>, int> S;
bool test(int i)
{
	int x = P[i].first, y = P[i].second;
	for(int x2 = x - 1; x2 <= x + 1; x2++)
		if(S.count(make_pair(x2, y - 1)))
			return true;
	return false;
}
bool ok(int i)
{
	int x = P[i].first, y = P[i].second;
	S.erase(P[i]);
	bool res = true;
	for(int x2 = x - 1; x2 <= x + 1; x2++)
	{
		pair<int, int> p(x2, y + 1);
		if(S.count(p) && !test(S[p])) res = false;
	}
	S[P[i]] = i;
	return res;
}

set<int> good;
void process(int i)
{
	int x = P[i].first, y = P[i].second;
	S.erase(P[i]);
	//cout << "process " << i << endl;
	for(int x2 = x - 2; x2 <= x + 2; x2++)
	{
		pair<int, int> p(x2, y - 1);
		if(S.count(p) && ok(S[p]))
			good.insert(S[p]);
		p = make_pair(x2, y);
		if(S.count(p) && !ok(S[p]))
		{
			//cout << "delete " << S[p] << ' ' << x2 << ' ' << y << endl;
			good.erase(S[p]);
		}
	}
}

int main()
{
	cin >> M;
	power[0] = 1;
	for(int i = 1; i <= 100003; i++) power[i] = (M * power[i - 1]) % mod;
	for(int i = 0; i < M; i++)
	{
		int x, y;
		cin >> x >> y;
		P[i] = make_pair(x, y);
		S[P[i]] = i;
	}
	for(int i = 0; i < M; i++)
		if(ok(i))
			good.insert(i);
	ll res = 0;
	for(int t = 0; t < M; t++)
	{
		int i;
		if(t % 2 == 0) i = *(--good.end());
		else i = *(good.begin());
		good.erase(i);
		process(i);
		cout << i << ' ';
		res += (i * power[M - 1 - t]) % mod;
	}
	cout << res % mod;
}
