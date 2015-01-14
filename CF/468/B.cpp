#include <iostream>
#include <cstring>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;

int N;
ll A, B;
map<ll, ll> X;
ll ans[100005];

set<ll> vis;
set<ll> cur;
void dfs(ll x)
{
	if(vis.count(x)) return;
	if(!X.count(x)) return;
	vis.insert(x);
	cur.insert(x);
	dfs(A - x);
	dfs(B - x);
}

bool color(ll C)
{
	for(set<ll>::iterator it = cur.begin(); it != cur.end(); it++)
	{
		ll x = *it;
		if(!cur.count(C - x)) return false;
	}
	return true;
}

int main()
{
	cin >> N >> A >> B;
	for(int i = 0; i < N; i++)
	{
		ll x;
		cin >> x;
		X[x] = i;
	}
	for(map<ll, ll>::iterator it = X.begin(); it != X.end(); it++)
	{
		ll x = it->first;
		dfs(x);
		if(color(A))
		{
			for(set<ll>::iterator it = cur.begin(); it != cur.end(); it++)
				ans[X[*it]] = 0;
			cur.clear();
		}
		else if(color(B))
		{
			for(set<ll>::iterator it = cur.begin(); it != cur.end(); it++)
				ans[X[*it]] = 1;
			cur.clear();
		}
		else
		{
			cout << "NO";
			return 0;
		}
	}
	cout << "YES\n";
	for(int i = 0; i < N; i++) cout << ans[i] << ' ';
}
