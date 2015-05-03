#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

ll solve(ll X, ll Y, ll S) // max B s.t. AX+BY=S
{
	if(X >= 100000)
	{
		while(true)
		{
			if(S % Y == 0) return S / Y;
			S -= X;
			if(S < 0) return -1;
		}
	}
	else
	{
		for(int i = 0; i < 100005; i++)
		{
			if(S % Y == 0) return S / Y;
			S -= X;
			if(S < 0) return -1;
		}
		return -1;
	}
}

int main()
{
	ll S, X, Y;
		ll M = 0;
		ll A0, O0;
		cin >> A0 >> O0 >> M >> X >> Y;
		M += (A0 * X + O0 * Y);
		ll F;
		cin >> F;
		S = M - F;
	ll B = solve(X, Y, S), A = solve(Y, X, S);
	if(A == -1)
	{
		assert(B == -1);
		cout << "Impossible\n";
	}
	else cout << A << ' ' << B << endl;
	return 0;
}
