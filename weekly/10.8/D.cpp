#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	while(true)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if(!a && !b && !c && !d) break;
		int cnt = 0;
		while(!(a == b && b == c && c == d))
		{
			int a2 = abs(a - b);
			int b2 = abs(b - c);
			int c2 = abs(c - d);
			int d2 = abs(d - a);
			a = a2, b = b2, c = c2, d = d2;
			cnt++;
		}
		cout << cnt << '\n';
	}
}
