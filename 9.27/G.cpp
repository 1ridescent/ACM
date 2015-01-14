#include <iostream>
#include <cmath>

using namespace std;

typedef pair<double, double> point;
#define x first
#define y second

point to(point u, point v)
{
	return point(v.x - u.x, v.y - u.y);
}

#define SQ(x) ((x) * (x))
double sqlen(point a, point b)
{
	return (SQ(a.x - b.x) + SQ(a.y - b.y));
}
double mn(point u)
{
	return SQ(u.x) + SQ(u.y);
}
double dot(point u, point v)
{
	return u.x * v.x + u.y * v.y;
}

int N;
double R;

point P[55];

double radius2(point a, point b, point c)
{
	double ls = (b.x * a.y + c.x * b.y + a.x * c.y);
	double rs = (a.x * b.y + b.x * c.y + c.x * a.y);
	double area = abs(ls - rs) / 2;
	double area2 = area * area;

	double abc2 = sqlen(a, b) * sqlen(b, c) * sqlen(c, a);

	return abc2 / (16.0 * area2);
}

int main()
{
	/*point a, b, c;
	cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
	cout << sqrt(r2(a, b, c));*/
	int tests;cin>>tests;while(tests--)
	{
		cin >> N >> R;
		R /= 2.0;

		for(int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;

		int best = 1;

		for(int i = 0; i < N; i++)
			for(int j = i + 1; j < N; j++)
			{
				point u = P[i], v = P[j];
				double r2 = sqlen(u, v) / 4;
				if(r2 > R) continue;

				point mid = point((u.x + v.x) / 2, (u.y + v.y) / 2);
				int num = 0;
				for(int k = 0; k < N; k++)
				{
					if(sqlen(mid, P[k]) <= r2) num++;
				}
				best = max(best, num);
			}

		for(int i = 0; i < N; i++)
			for(int j = i + 1; j < N; j++)
				for(int k = j + 1; k < N; k++)
				{
					point u = P[i], v = P[j], w = P[k];
					double r2 = radius2(u, v, w);
					if(r2 > R) continue;

					int num = 0;
					for(int l = 0; l < N; l++)
					{
						point p = P[l];
						if(sqlen(p, u) * sqlen(p, v) * sqlen(p, w) == 0) num++;

						point a = to(v, u), b = to(v, w), c = to(p, w), d =to(p, u);
						double cos1 = SQ(dot(a, b)) / (mn(a) *  mn(b));
						double cos2 = SQ(dot(c, d)) / (mn(c) * mn(d));
						if(dot(c, d) < 0) cos2 *= -1;

						if(cos2 < cos1) num++;
					}
					best = max(best, num);
				}

		cout << best << endl;
	}
}
