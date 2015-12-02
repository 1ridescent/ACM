#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll choose2(ll n)
{
	return n * (n - 1) / 2;
}
ll urns3(ll n)
{
	if(n < 0) return 0;
	return choose2(n + 2);
}

ll num(ll a, ll b, ll c, ll l)
{
	return urns3(l - a - b - c);
}

ll A, B, C;
ll get(ll L)
{
	ll T = (L - 1) / 2 + 1;
	ll A2 = max(A, T);
	ll B2 = max(B, T);
	ll C2 = max(C, T);
	return num(A,B,C,L) - num(A2,B,C,L) - num(A,B2,C,L) - num(A,B,C2,L)
			+ num(A2,B2,C,L) + num(A2,B,C2,L) + num(A,B2,C2,L)
			- num(A2,B2,C2,L);
}

int main()
{
	ll L;
	cin >> A >> B >> C >> L;
	L += A + B+ C;
	ll ans = 0;
	for(int l = 0; l <= L; l++) ans += get(l);
	cout << ans;
}
