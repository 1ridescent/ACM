#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;
ll best[10], num[10];

int main()
{
	for(int i = 0; i <= 9; i++) best[i] = 10000;
	for(int a = 0; a <= 9; a++)
		for(int b = 0; b <= 9; b++)
			for(int c = 0; c <= 9; c++)
				for(int d = 0; d <= 9; d++)
				{
					int s = a * 1 + b * 2 + c * 3 + d * 5;
					int n = a + b + c + d;
					if(s <= 9)
					{
						if(n == best[s]) num[s]++;
						else if(n < best[s]) best[s] = n, num[s] = 1;
					}
				}
	//for(int i = 0; i <= 9; i++) printf("%d: %d %d\n", i, (int)best[i], (int)num[i]);
	int t;
	cin >> t;
	while(t--)
	{
		ll W;
		int C;
		cin >> W >> C;
		if(W % 1000 != 0)
		{
			printf("0\n");
			continue;
		}
		W /= 1000;
		ll s = 0, n = 1;
		for(int c = 0; c < C; c++)
		{
			s += best[W % 10];
			n *= num[W % 10];
			W /= 10;
		}
		if(W >= 10)
		{
			ll w = 5 + W % 5;
			s += (W - w) / 5;
			W = w;
		}
		s += best[W];
		n *= num[W];
		cout << s << ' ' << n << '\n';
	}
}
