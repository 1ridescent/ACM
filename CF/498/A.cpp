#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
	ll sx, sy, tx, ty;
	cin >> sx >> sy >> tx >> ty;
	int N;
	cin >> N;
	int ans = 0;
	while(N--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		int t1 = (a * sx + b * sy - c > 0);
		int t2 = (a * tx + b * ty - c > 0);
		if(t1 + t2 == 1) ans++;
	}
	cout << ans;
}


