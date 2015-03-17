#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
const double EPS = 1e-8;

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
    Point operator*(ll s)
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

ll dot(Point p, Point q)
{
    return p.x * q.x + p.y * q.y;
}
ll cross(Point p, Point q)
{
    return p.x * q.y - p.y * q.x;
}

ll sqdist(Point v)
{
    return v.x * v.x + v.y * v.y;
}

bool cmp(Point p, Point q)
{
    return p.x < q.x;
}

Point rotate(Point p, double theta)
{
    return Point(cos(theta) * p.x + sin(theta) * p.y, -sin(theta) * p.x + cos(theta) * p.y);
}

vector<Point> upper_hull(vector<Point> P)
{
    sort(P.begin(), P.end(), cmp);
    vector<int> S;
    for(int i = 0; i < P.size(); i++)
    {
        while(S.size() >= 2)
        {
            Point A = P[S[S.size() - 2]], B = P[S[S.size() - 1]], C = P[i];
            if(cross(A - B, C - B) < EPS) S.pop_back();
            else break;
        }
        S.push_back(i);
    }
    vector<Point> res;
    for(int i = 0; i < S.size(); i++) res.push_back(P[S[i]]);
    return res;
}

vector<Point> convex_hull(vector<Point> P)
{
	for(int i = 0; i < P.size(); i++) P[i] = rotate(P[i], 1.0);
	vector<Point> hull = upper_hull(P);
	for(int i = 0; i < P.size(); i++) P[i] = P[i] * -1;
	vector<Point> LH = upper_hull(P);
	for(int i = 0; i < LH.size(); i++) LH[i] = LH[i] * -1;
	for(int i = 1; i < LH.size() - 1; i++) hull.push_back(LH[i]);
	for(int i = 0; i < hull.size(); i++) hull[i] = rotate(hull[i], -1.0);
	//for(int i = 0; i < hull.size(); i++) cout << '(' << hull[i].x << ',' << hull[i].y << ")\n";
	return hull;
}

bool in_triangle(Point a, Point b, Point c, Point m)
{
	return abs(abs(cross(a - m, b - m)) + abs(cross(b - m, c - m)) + abs(cross(c - m, a - m)) - abs(cross(b - a, c - a))) < EPS;
}

int N;
vector<Point> P;

ll num[55][55][55];
ll get_num(int a, int b, int c)
{
	if(a == b || b == c || c == a) return -1;
	if(num[a][b][c] != -1) return num[a][b][c];
	num[a][b][c] = 0;
	for(int m = 0; m < N; m++)
	{
		if(m == a || m == b || m == c) continue;
		if(in_triangle(P[a], P[b], P[c], P[m]))
		{
			//cout << m << " is in " << a << ' ' << b << ' ' << c << endl;
			num[a][b][c] += get_num(a, b, m) * get_num(b, c, m) * get_num(c, a, m);
		}
	}
	if(num[a][b][c] == 0) num[a][b][c] = 1;
	//cout << a << ' ' << b << ' ' << c << ": " << num[a][b][c] << endl;
	return num[a][b][c];
}

vector<Point> hull;
int K;

ll total[55][55];
ll dp(int l, int r)
{
	//cout << "l r = " << l << ' ' << r << endl;
	if(total[l][r] != -1) return total[l][r];
	if((r - l + K) % K <= 1) total[l][r] = 1;
	else
	{
		total[l][r] = 0;
		for(int m = (l + 1) % K; m % K != r; m = (m + 1) % K)
		{
			//cout << "m = " << m << endl;
			total[l][r] += dp(l, m) * dp(m, r) * num[l][m][r];
		}
	}
	//cout << l << ' ' << r << ": " << total[l][r] << endl;
	return total[l][r];
}

int main()
{
	if(fopen("tria.in", "r")) freopen("tria.in", "r", stdin), freopen("tria.out", "w", stdout);
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		Point p;
		cin >> p.x >> p.y;
		P.push_back(p);
	}
	hull = convex_hull(P);
	K = hull.size();

	vector<Point> temp = P;
	P.clear();
	for(int i = 0; i < K; i++) P.push_back(hull[i]);
	for(int i = 0; i < N; i++)
	{
		bool contains = false;
		for(int j = 0; j < P.size(); j++)
		{
			if(sqdist(temp[i] - P[j]) < EPS) contains = true;
		}
		if(!contains) P.push_back(temp[i]);
	}
	//for(int i = 0; i < P.size(); i++) cout << '(' << P[i].x << ',' << P[i].y << ")\n";

	for(int a = 0; a < N; a++)
		for(int b = 0; b < N; b++)
			for(int c = 0; c < N; c++)
				num[a][b][c] = -1;
	for(int a = 0; a < N; a++)
		for(int b = 0; b < N; b++)
			for(int c = 0; c < N; c++)
				get_num(a, b, c);

	for(int l = 0; l < hull.size(); l++)
		for(int r = 0; r < hull.size(); r++)
			total[l][r] = -1;

	cout << dp(0, K - 1) << endl;
	return 0;
}
