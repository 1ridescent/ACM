#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define left Left
#define right Right

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
bool intersects(Segment S, Segment T)
{
    Point A = S.s, B = T.s, C = S.t, D = T.t;
    Point u = A - B, v = A - C, w = A - D;
    if(cross(v, u) * cross(v, w) >= 0) return false;
    u = B - A, v = B - D, w = B - C;
    if(cross(v, u) * cross(v, w) >= 0) return false;
    return true;
}
bool on_line(Point p, Segment S)
{
	return (cross(S.s - p, S.t - p) == 0 && dot(S.s - p, S.t - p) < 0);
}

int N;
vector<Point> P;
bool D[205][205]; // diagonal valid? i.e. doesn't intersect?
ll dp[205][205];

ll area(vector<Point>& V)
{
	ll total = 0;
	for(int i = 0; i < V.size(); i++) total += cross(V[i], V[(i + 1) % V.size()]);
	return abs(total);
}

bool valid(int i, int j)
{
	if(i == j) return false;
	if((i + 1) % N == j || (j + 1) % N == i) return true;
	for(int k = 0; k < N; k++)
	{
		if(intersects(Segment(P[k], P[(k + 1) % N]), Segment(P[i], P[j]))) return false;
		if(on_line(P[k], Segment(P[i], P[j]))) return false;
	}
	vector<Point> left, right;
	for(int k = i; k != (j + 1) % N; k = (k + 1) % N) left.push_back(P[k]);
	for(int k = j; k != (i + 1) % N; k = (k + 1) % N) right.push_back(P[k]);
	//cout << i << ' ' << j << ": " << area(left) << ' ' << area(right) << ' ' << area(P) << endl;
	return area(left) + area(right) == area(P);
}

ll calc(int i, int j) // [i, j]
{
	if(dp[i][j] != -1) return dp[i][j];

	if(i == j) dp[i][j] = 1;
	else if((i + 1) % N == j) dp[i][j] = 1;
	else
	{
		dp[i][j] = 0;
		for(int k = (i + 1) % N; k != j; k = (k + 1) % N)
		{
			if(D[k][i] && D[k][j])
			{
				dp[i][j] += calc(i, k) * calc(k, j);
				dp[i][j] %= mod;
			}
		}
	}

	//cout << i << ' ' << j << ": " << dp[i][j] << endl;
	return dp[i][j];
}

int main()
{
	cin >> N;
	P = vector<Point>(N);
	for(int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;

	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			D[i][j] = valid(i, j);
			//cout << i << ' ' << j << " - " << D[i][j] << endl;
		}

	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			dp[i][j] = -1;

	cout << calc(0, N - 1) << endl;
}
