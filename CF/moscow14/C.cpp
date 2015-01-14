#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main()
{
	ll D, C, S;
	cin >> D >> C >> S;
	ll nd, nc;
	if(C <= D)
	{
		nd = nc = (S + C - 1) / C;
	}
	else
	{
		nd = (S + D - 1) / D;
		ll low = 0, high = nd;
		while(low + 1 < high)
		{
			ll mid = (low + high) / 2;
			ll c1 = nd / mid;
			ll c2 = c1 + 1;
			ll nc2 = nd % mid;
			ll nc1 = mid - nc2;
			ll s = nc1 * min(c1 * D, C) + nc2 * min(c2 * D, C);
			if(s >= S) high = mid;
			else low = mid;
		}
		nc = high;
	}
	cout << nd << ' ' << nc << endl;
}
