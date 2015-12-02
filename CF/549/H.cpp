#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

ld ans = 1e100;
void solve(ld a, ld b, ld c)
{
//	cout << "a = " << a << "  b = " << b << "  c = " << c << endl;
	if(abs(a) < 1e-9)
	{
		if(abs(b) < 1e-9)
		{
			if(abs(c) < 1e-9) ans = 0.0;
			else return;
		}
		ld s = -c / b;
		ans = min(ans, abs(s));
		return;
	}
	ld s = -b / (2.0 * a);
	ld r = b * b - 4 * a * c;
	if(r >= -1e-9)
	{
		if(r < 0.0) r = 0;
		ld t = sqrt(r) / (2.0 * a);
//		cout << "s = " << s << "  t = " << t << endl;
		ans = min(ans, abs(s + t));
		ans = min(ans, abs(s - t));
	}
}
void process(ld p, ld q, ld r, ld s, ld& a, ld& b, ld& c)
{
	a += q * s;
	b += p * s + q * r;
	c += p * r;
}

#define FOR(i) for(int i = -1; i <= 1; i += 2)

int main()
{
	ld a, b, c, d;
	cin >> a >> b >> c >> d;
	FOR(da) FOR(db) FOR(dc) FOR(dd)
	{
		ld a2 = 0, b2 = 0, c2 = 0;
		process(a, da, d, dd, a2, b2, c2);
		process(-b, -db, c, dc, a2, b2, c2);
		solve(a2, b2, c2);
	}
	printf("%.12f\n", (double)ans);
}
