#include <bits/stdc++.h>

using namespace std;


typedef long long ll;

typedef complex<ll> Point;
#define x real()
#define y imag()

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
	return make_pair(p.x, p.y) < make_pair(q.x, q.y);
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
            if(cross(A - B, C - B) < 0) S.pop_back();
            else break;
        }
        S.push_back(i);
    }
    vector<Point> res;
    for(int i = 0; i < S.size(); i++) res.push_back(P[S[i]]);
    return res;
}

map<ll, ll> maxes;
vector<Point> P;
int N;
map<pair<ll, ll>, vector<int> > ids;
vector<int> res;

int main()
{
	cin >> N;
	ll maxX = 0, maxY = 0;
	for(int i = 0; i < N; i++)
	{
		ll X, Y;
		cin >> X >> Y;
		maxX = max(maxX, X);
		maxY = max(maxY, Y);
		if(!ids.count(make_pair(X, Y)))
			maxes[X] = max(maxes[X], Y);//P.push_back(Point(X, Y));
		ids[make_pair(X, Y)].push_back(i + 1);
	}
	P.push_back(Point(maxX + 1, -100000000LL));
	P.push_back(Point(-10000000000LL, maxY + 1));
	for(map<ll, ll>::iterator it = maxes.begin(); it != maxes.end(); it++)
		P.push_back(Point(it->first, it->second));
	P = upper_hull(P);
	for(int i = 0; i < P.size(); i++)
	{
		//cout << P[i] << ' ';
		vector<int>& v = ids[make_pair(P[i].x, P[i].y)];
		for(int j = 0; j < v.size(); j++)
		{
			assert(1 <= v[j] && v[j] <= N);
			res.push_back(v[j]);
		}
	}
	sort(res.begin(), res.end());
	assert(!res.empty());
	for(int i = 0; i < res.size(); i++) cout << res[i] << ' ';
}
