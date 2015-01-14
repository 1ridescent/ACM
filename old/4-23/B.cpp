#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>

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
bool intersects(Segment S, Segment T)
{
    Point A = S.s, B = T.s, C = S.t, D = T.t;
    Point u = A - B, v = A - C, w = A - D;
    if(cross(v, u) * cross(v, w) > 0) return false;
    u = B - A, v = B - D, w = B - C;
    if(cross(v, u) * cross(v, w) > 0) return false;
    return true;
}

int N, C;
map<pair<int, int>, vector< pair<int, int> > > edges;
vector<pair<int, int> > unused;
set<pair<int, int> > used;
vector<Segment> P[1010];
int nextid = 0;

map<vector<int>, int> freq;

int main()
{
	cin >> N >> C;
	for(int i = 0; i < N; i++)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		unused.push_back(make_pair(x1, y1));
		unused.push_back(make_pair(x2, y2));
		edges[make_pair(x1, y1)].push_back(make_pair(x2, y2));
		edges[make_pair(x2, y2)].push_back(make_pair(x1, y1));
	}
	for(int i = 0; i < unused.size(); i++)
	{
		if(used.find(unused[i]) != used.end()) continue;
		pair<int, int> init = unused[i];
		pair<int, int> cur = init;
		pair<int, int> prev = make_pair(1000007, 1000008);
		while(true)
		{
			int j = 0;
			while(edges[cur][j] == prev) j++;
			prev = cur;
			cur = edges[cur][j];
			used.insert(prev);
			used.insert(cur);
			Segment S(Point(prev.first, prev.second), Point(cur.first, cur.second));
			P[nextid].push_back(S);
			if(cur == init) break;
		}
		//for(int i = 0; i < P[nextid].size(); i++) printf("(%lld,%lld)<->(%lld,%lld) ",P[nextid][i].s.x,P[nextid][i].s.y,P[nextid][i].t.x,P[nextid][i].t.y); cout << endl;
		nextid++;
	}
	int best = 0;
	for(int c = 0; c < C; c++)
	{
		Point p;
		cin >> p.x >> p.y;
		Segment S(p, p + Point(1000007, 1000008));
		vector<int> v;
		for(int i = 0; i < nextid; i++)
		{
			int b = 0;
			for(int j = 0; j < P[i].size(); j++)
			{
				if(intersects(S, P[i][j])) b ^= 1;
			}
			v.push_back(b);
		}
		//for(int i = 0; i < v.size(); i++) cout << v[i]; cout << endl;
		freq[v]++;
		best = max(best, freq[v]);
	}
	cout << best << endl;
}
