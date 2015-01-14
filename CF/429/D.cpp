#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

class Point
{
public:
    ll x, y;
    Point() { }
    Point(ll x, ll y)
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

vector<Point> upper_hull(vector<Point> P)
{
    sort(P.begin(), P.end(), cmp);
    vector<int> S;
    for(int i = 0; i < P.size(); i++)
    {
        while(S.size() >= 2)
        {
            Point A = P[S[S.size() - 2]], B = P[S[S.size() - 1]], C = P[i];
            if(cross(A - B, C - B) <= 0) S.pop_back();
            else break;
        }
        S.push_back(i);
    }
    vector<Point> res;
    for(int i = 0; i < S.size(); i++) res.push_back(P[S[i]]);
    return res;
}

int N;
ll A[100100];
vector<Point> P;

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> A[i];
	for(int i = 1; i < N; i++) A[i] += A[i - 1];
	for(int i = 0; i < N; i++) P.push_back(Point(i, A[i]));
	vector<Point> hull = upper_hull(P);
	//for(int i = 0; i < hull.size(); i++) cout << hull[i].x << ' '<< hull[i].y << endl;
	int r = P.size() - 1;

	for(int i = 0; i < N; i++) P[i] = P[i] * -1;
	vector<Point> LH = upper_hull(P);
	for(int i = 0; i < LH.size(); i++) LH[i] = LH[i] * -1;
	for(int i = 1; i < LH.size() - 1; i++) hull.push_back(LH[i]);
	for(int i = 0; i < hull.size(); i++) cout << hull[i].x << ' ' << hull[i].y << endl;

	int l = 0;
	ll best = sqdist(hull[l] - hull[r]);
	for(int t = 0; t < N; t++)
	{
		if(cross(hull[(l + 1) % hull.size()] - hull[l], hull[(r + 1) % hull.size()] - hull[r]) >= 0)
		{
			l = (l + 1) % hull.size();
		}
		else r = (r + 1) % hull.size();
		best = max(best, sqdist(hull[l] - hull[r]));
	}

	cout << best << endl;
}
