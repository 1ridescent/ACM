#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

typedef pair<double, double> point;
#define x first
#define y second

point P[4];

point rot(point p)
{
	return point(cos(1) * p.x + sin(1) * p.y, -sin(1) * p.x + cos(1) * p.y);
}

point to(point u, point v)
{
	return point(v.x - u.x, v.y - u.y);
}

double len(point p)
{
	return sqrt(p.x * p.x + p.y * p.y);
}

point inters(point a1, point a2, point b1, point b2)
{
	double m1 = (a2.y - a1.y) / (a2.x - a1.x);
	double d1 = a1.y - m1 * a1.x;
	double m2 = (b2.y - b1.y) / (b2.x - b1.x);
	double d2 = b1.y - m2 * b1.x;

	double x = (d2 - d1) / (m1 - m2);
	double y = m1 * x + d1;
	return point(x, y);
}

double area(point a, point b, point c)
{
	double A = len(to(b, c));
	double B = len(to(a, c));
	double C = len(to(a, b));
	double S = (A + B + C) / 2;
	return sqrt(S * (S - A) * (S - B) * (S - C));
}
double perim(point a, point b, point c)
{
	double A = len(to(b, c));
	double B = len(to(a, c));
	double C = len(to(a, b));
	return (A + B + C);
}

int main()
{
	cout << setprecision(3) << fixed;
	while(true)
	{
		bool done = true;
		for(int i = 0; i < 4; i++)
		{
			cin >> P[i].x >> P[i].y;
			if(P[i].x != 0 || P[i].y != 0) done = false;
			P[i] = rot(P[i]);
		}
		//cout << "Asdf " << endl;
		if(done) break;

		point I = inters(P[0], P[2], P[1], P[3]);

		pair<double, double> data[4];
		for(int i = 0; i < 4; i++)
		{
			double a = area(P[i], P[(i + 1) % 4], I);
			double p = perim(P[i], P[(i + 1) % 4], I);
			a = ((int)(a * 1000.0 + 0.5)) / 1000.0;
			p = ((int)(p * 1000.0 + 0.5)) / 1000.0;
			data[i] = make_pair(a, p);
		}
		sort(data, data + 4);
		for(int i = 3; i >= 0; i--)
		{
			cout << data[i].first << ' ' << data[i].second;
			if(i) cout << ' ';
		}
		cout << '\n';
	}
}
