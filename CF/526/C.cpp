#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	ll C, Ha, Hb, Wa, Wb;
	cin >> C >> Ha >> Hb >> Wa >> Wb;
	if(Wa > Wb)
	{
		swap(Wa, Wb);
		swap(Ha, Hb);
	}
	ll ans = 0;
	if(Wb >= 10000)
	{
		for(ll b = 0; b <= C / Wb; b++)
		{
			ll a = (C - b * Wb) / Wa;
			ans = max(ans, a * Ha + b * Hb);
		}
	}
	else
	{
		for(ll b = 0; b <= 100000 && b <= C / Wb; b++)
		{
			ll a = (C - b * Wb) / Wa;
			ans = max(ans, a * Ha + b * Hb);
		}
		for(ll a = 0; a <= 100000 && a <= C / Wa; a++)
		{
			ll b = (C - a * Wa) / Wb;
			ans = max(ans, a * Ha + b * Hb);
		}
	}
	cout << ans;
}
