#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<double, double> point;
#define x first
#define y second

point A, B, C;

#define SQ(x) ((x) * (x))
inline double dist(point p, point q)
{
	return sqrt( SQ(p.x - q.x) + SQ(p.y - q.y) );
}

int main()
{
	freopen("bomb.in", "r", stdin); freopen("bomb.out", "w", stdout);

	cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
	double a = dist(B, C), b = dist(C, A), c = dist(A, B);
	//printf("%lf %lf %lf", a,b,c);
	double p = 0.5 * (a + b + c);
	double r = p - a, s = p - b, t = p - c;
	printf("%.9f\n%.9f\n%.9f\n", r, s, t);
	return 0;
}
