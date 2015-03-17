#include <bits/stdc++.h>

using namespace std;

int main()
{
	int N;
	cin >> N;
	long long ans = 0;
	int cur = 0;
	while(N--)
	{
		int x;
		cin >> x;
		if(x < cur)
		{
			ans += (cur - x);
		}
		cur = x;
	}
	cout << ans + cur << endl;
}
