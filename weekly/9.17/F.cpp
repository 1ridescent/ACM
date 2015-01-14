#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;

class Point
{
public:
	ll x, y;
	int id; // id in segs[N]
	char type; // l or r
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
	int id;
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

inline bool between(ll x, ll l, ll r)
{
	return (l <= x && x <= r);
}

inline bool cmp_vertical(Segment S, Segment T)
{
	Point P;
	Segment L;
	if(between(S.s.x, T.s.x, T.t.x)) P = S.s, L = T;
	else if(between(S.t.x, T.s.x, T.t.x)) P = S.t, L = T;
	else
	{
		return !cmp_vertical(T, S);
	}
	Point u = L.s - P, v = L.t - P;
	//cout << u.x << ' ' << u.y << ' ' << v.x << ' ' << v.y << endl;
	return (cross(u, v) <= 0);
}
class SegmentCompareVertical
{
public:
	bool operator()(Segment S, Segment T)
	{
		return cmp_vertical(S, T);
	}
};

bool cmp_start(Point S, Point T)
{
	if(S.x < T.x) return true;
	if(S.x > T.x) return false;
	return (S.y > T.y);
}
bool cmp_end(Point S, Point T)
{
	if(S.x > T.x) return true;
	if(S.x < T.x) return false;
	return (S.y > T.y);
}

bool slope_left(Segment S)
{
	return (S.s.y < S.t.y);
}

int N;
Segment segs[40040];
vector<Point> points;

typedef set<Segment, SegmentCompareVertical> seg_set_type;
seg_set_type seg_set;

vector<int> flow_from[40040]; // a -> b : b flows to a

vector<Point> flow_points[40040];
ll flow_vals[40040];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		Segment S;
		cin >> S.s.x >> S.s.y >> S.t.x >> S.t.y;
		S.id = i;
		segs[i] = S;
		Point s = S.s, t = S.t;
		s.id = t.id = i;
		s.type = 'l', t.type = 'r';
		points.push_back(s);
		points.push_back(t);
	}

	sort(points.begin(), points.end(), cmp_start);
	for(int pi = 0; pi < N; pi++)
	{
		cout << pi << endl;
		Point P = points[pi];
		if(P.type == 'l') // insert seg
		{
			Segment S = segs[P.id];
			seg_set.insert(S);
		}
		else
		{
			Segment S = segs[P.id];
			if(!slope_left(S))
			{
				seg_set_type::iterator it = seg_set.find(S);
				if(it != seg_set.begin())
				{
					it--;
					Segment T = *it; // S flows onto T
					cout << S.id << " -> " << T.id << endl;
					flow_points[T.id].push_back(P);
					flow_from[T.id].push_back(S.id);
				}
			}
			seg_set.erase(S);
		}
	}
return 0;
	sort(points.begin(), points.end(), cmp_end);
	for(int pi = 0; pi < N; pi++)
	{
		Point P = points[pi];
		if(P.type == 'r') // insert seg
		{
			Segment S = segs[P.id];
			seg_set.insert(S);
		}
		else
		{
			Segment S = segs[P.id];
			if(slope_left(S))
			{
				seg_set_type::iterator it = seg_set.find(S);
				if(it != seg_set.begin())
				{
					it--;
					Segment T = *it; // S flows onto T
					cout << S.id << " -> " << T.id << endl;
					flow_points[T.id].push_back(P);
					flow_from[T.id].push_back(S.id);
				}
			}
			seg_set.erase(S);
		}
	}

}
