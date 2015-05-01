#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll H, W;
set<ll> HX, WX;
set<pair<ll, pair<ll, ll> > > HS, WS;

void add(ll a, ll b, set<pair<ll, pair<ll, ll> > >& S)
{
	S.insert(make_pair(b - a, make_pair(a, b)));
}
void remove(ll a, ll b, set<pair<ll, pair<ll, ll> > >& S)
{
	S.erase(make_pair(b - a, make_pair(a, b)));
}
void divide(ll b, set<pair<ll, pair<ll, ll> > >& S, set<ll>& X)
{
	set<ll>::iterator it = X.lower_bound(b);
	ll c = *it;
	it--;
	ll a = *it;
	X.insert(b);
	remove(a, c, S);
	add(a, b, S);
	add(b, c, S);
}

int main()
{
	cin >> W >> H;
	HX.insert(0); HX.insert(H);
	WX.insert(0); WX.insert(W);
	add(0, H, HS);
	add(0, W, WS);
	int N;
	cin >> N;
	while(N--)
	{
		char t;
		ll x;
		cin >> t >> x;
		if(t == 'H') divide(x, HS, HX);
		else divide(x, WS, WX);
		cout << (--HS.end())->first * (--WS.end())->first << '\n';
	}
}
