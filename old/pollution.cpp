#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const double EPS = 1e-7;
const int NUM = 10000;

// time before first submit = 1:20

class Point
{
public:
    double x, y;
    Point() { }
    Point(double x, double y)
    {
        this->x = x, this->y = y;
    }
    Point operator+(Point q)
    {
        return Point(x + q.x, y + q.y);
    }
    Point operator-(Point q)
    {
        return Point(x - q.x, y - q.y);
    }
    Point operator*(double s)
    {
        return Point(s * x, s * y);
    }
};
class Segment
{
public:
    Point s, t;
    Segment() { }
    Segment(Point s, Point t)
    {
        this->s = s, this->t = t;
    }
};

double dot(Point p, Point q)
{
    return p.x * q.x + p.y * q.y;
}
double cross(Point p, Point q)
{
    return p.x * q.y - p.y * q.x;
}
bool intersects(Segment S, Segment T)
{
    Point A = S.s, B = T.s, C = S.t, D = T.t;
    Point u = A - B, v = A - C, w = A - D;
    if(cross(v, u) * cross(v, w) > EPS) return false;
    u = B - A, v = B - D, w = B - C;
    if(cross(v, u) * cross(v, w) > EPS) return false;
    return true;
}

double length(Point v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}
Point proj(Point u, Point v)
{
	return v * (dot(u, v) / dot(v, v));
}
double dist(Point p, Segment S)
{
	Point u = S.s - p, v = S.t - p;
	return abs(cross(u, v)) / length(S.s - S.t);
}

Point null(-1,-1);
bool is_null(Point p)
{
	return (p.x < -0.5 && p.y < -0.5);
}

int N;
double R;
Point P[333];
vector<Point> poly;

Point circle_intersect(Segment S) // length(S.s) < R, length(S.t) > R
{
	double low = 0, high = 1;
	while(low + EPS*EPS < high)
	{
		double mid = (low+high)/2;
		//cout << mid << ' ' << (S.s*mid + S.t*(1-mid)).x << ' ' << (S.s*mid + S.t*(1-mid)).y << ' ' << length(S.s*mid+S.t*(1-mid)) << endl;
		if(length(S.s*mid + S.t*(1-mid)) > R) low = mid;
		else high = mid;
	}
	//printf("(%lf,%lf) (%lf,%lf) (%lf,%lf)\n", S.s.x,S.s.y,(S.s*low + S.t*(1-low)).x,(S.s*low + S.t*(1-low)).y,S.t.x,S.t.y);
	return S.s*low + S.t*(1-low);
}
double shoelace(const vector<Point>& poly)
{
	double area = 0;
	for(int i = 0; i < poly.size(); i++)
	{
		area += cross(poly[i], poly[(i+1)%poly.size()]);
	}
	return abs(area/2);
}

int main()
{
	cin >> N >> R;
	for(int i = 0; i < N; i++)
	{
		cin >> P[3 * i].x >> P[3 * i].y;
		P[3*i+1] = P[3*i+2] = null;
	}
	P[3 * N] = P[0];
	for(int i = 0; i < N; i++)
	{
		Segment S(P[3*i], P[3*(i+1)]);
		//printf("(%lf,%lf) (%lf,%lf)\n", S.s.x,S.s.y,S.t.x,S.t.y);
		if(length(S.s) < R && length(S.t) > R)
			P[3*i+1] = circle_intersect(S);
		else if(length(S.s) > R && length(S.t) < R)
		{
			swap(S.s, S.t);
			P[3*i+1] = circle_intersect(S);
		}
		else if(length(S.s) > R && length(S.t) > R)
		{
			double d = dist(Point(0,0), S);
			if(d < R)
			{
				Point closest = S.s + proj(S.s * -1, S.t-S.s);
				P[3*i+1] = circle_intersect(Segment(closest, S.s));
				P[3*i+2] = circle_intersect(Segment(closest, S.t));
			}
		}
	}
	int start = 0;
	while(start < 3*N && !(!is_null(P[start]) && length(P[start]) < R + EPS))
	{
		start++;
	}
	if(start == 3*N)
	{
		cout << "0\n";
		return 0;
	}
	//for(int i = 0; i < 3*N; i++) printf("(%lf,%lf) ", P[i].x, P[i].y);
	int cur = start;
	while(cur != start+3*N)
	{
		Point left = P[cur%(3*N)];
		double langle = atan2(left.y, left.x);
		poly.push_back(P[cur%(3*N)]);
		cur++;
		while(is_null(P[cur%(3*N)])) cur++;
		//printf("(%lf,%lf) %lf<%lf: ",P[cur%(3*N)].x,P[cur%(3*N)].y,length(P[cur%(3*N)]),R+EPS);
		//cout << (length(P[cur%(3*N)]) > R+EPS) << endl;
		if(length(P[cur%(3*N)]) > R + EPS)
		{
			while(!(!is_null(P[cur%(3*N)]) && length(P[cur%(3*N)]) < R + EPS)) cur++;
			Point right = P[cur%(3*N)];
			//printf("(%lf,%lf) (%lf,%lf)\n", left.x,left.y,right.x,right.y);
			double rangle = atan2(right.y, right.x);
			for(int i = 1; i < NUM; i++)
			{
				double t = ((double)(i)) / NUM;
				double a = langle * (1-t) + rangle * t;
				poly.push_back(Point(cos(a), sin(a)) * R);
			}
		}
	}
	//for(int i = 0; i < poly.size(); i++) printf("(%lf,%lf) ", poly[i].x, poly[i].y);
	printf("%.12f\n", shoelace(poly));
}
