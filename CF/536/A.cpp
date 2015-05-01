#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll val[1000005];
ll partial[1000005];
map<ll, int> P, V;

int main()
{
	ios::sync_with_stdio(false);
	ll A, B, N;
	cin >> A >> B >> N;
	P[0] = -1;
	V[0] = -1;
	for(int i = 1; i <= 1000002; i++)
	{
		val[i] = A + B * (i - 1);
		partial[i] = partial[i - 1] + val[i];
		P[partial[i]] = i;
		V[val[i]] = i;
	}
	while(N--)
	{
		ll L, T, M;
		cin >> L >> T >> M;
		int x = min((--P.upper_bound(T * M + partial[L - 1]))->second, (--V.upper_bound(T))->second);
		if(x < L) cout << "-1\n";
		else cout << x << '\n';
	}
}
