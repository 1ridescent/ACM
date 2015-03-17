#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> point;
#define x first
#define y second

int N;
double D;
point P[3005];

point rotate(point p)
{
	double a = 123.456789;
	return point(cos(a) * p.x + sin(a) * p.y, -sin(a) * p.x + cos(a) * p.y);
}
double dist(point u, point v)
{
	return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
}

int main2()
{
	point p0;
	cin >> p0.x >> p0.y;
	cin >> D >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> P[i].x >> P[i].y;
		P[i].x -= p0.x;
		P[i].y -= p0.y;
		//P[i] = rotate(P[i]);
	}
	p0 = point(0, 0);
	int ans = 0;
	for(int t = 1; t <= N; t++)
	{
		double x = P[t].x, y = P[t].y;
		double sr = sqrt(x * x + y * y);
		point corner(D * x / sr, D * y / sr);
		int cnt = 0;
		for(int i = 1; i <= N; i++)
			if(abs(dist(p0, P[i]) + dist(P[i], corner) - dist(p0, corner)) < 1e-8) cnt++;
		map<double, int> angle;
		int same = 0;
		for(int i = 1; i <= N; i++)
		{
			if(abs(dist(corner, P[i])) < 1e-8)
			{
				same++;
				continue;
			}
			double a = atan2(P[i].y - corner.y, P[i].x - corner.x);
			map<double, int>::iterator it = angle.upper_bound(a - 1e-8);
			if(it != angle.end() && abs(it->first - a) < 1e-8)
				it->second++;
			else angle[a]++;
		}
		int add = 0;
		for(map<double, int>::iterator it = angle.begin(); it != angle.end(); it++)
			add = max(add, it->second);
		ans = max(ans, cnt * (same + add));
	}
	cout << ans << '\n';
}

int main()
{
	int T;
	cin >> T;
	for(int i = 1; i <= T; i++)
	{
		printf("Case #%d: ", i);
		main2();
	}
}
