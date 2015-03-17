#include <bits/stdc++.h>

using namespace std;

int L[305], C[305];
map<int, int> dp;
int main()
{
	int N;
	cin >> N;
	for(int i = 0; i < N; i++) cin >> L[i];
	for(int i = 0; i < N; i++) cin >> C[i];
	for(int i = 0; i < N; i++)
	{
		int x = L[i], c = C[i];
		for(int i = 2; i * i <= x; i++)
		{
			while(x % (i * i) == 0) x /= i;
		}
		//cout << x << ' ' << c << endl;
		dp[0] = 0;
		for(map<int, int>::iterator it = dp.begin(); it != dp.end(); it++)
		{
			int g = __gcd(it->first, x);
			if(!dp.count(g)) dp[g] = it->second + c;
			else dp[g] = min(dp[g], it->second + c);
		}
	}
	if(!dp.count(1)) cout << -1;
	else cout << dp[1];
}
