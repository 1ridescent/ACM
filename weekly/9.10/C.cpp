#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<double, double> point;
#define x first
#define y second

const double PI = acos(-1);
const double EPS = 1e-8;

int N;
double R;
point P[2020];

point to(point s, point t)
{
	return point(t.x - s.x, t.y - s.y);
}
double len(point v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}
double dist(point a, point b)
{
	return len(to(a, b));
}

bool cmp(point u, point v)
{
	return atan2(u.y, u.x) < atan2(v.y, v.x);
}

vector<pair<double, char> > V;
int cnt(int o)
{
	V.clear();
	for(int i = 0; i < N; i++)
	{
		if(i == o) continue;
		if(dist(P[i], P[o]) > 2 * (R + 1e-6)) continue;
		point v = to(P[o], P[i]);
		double dir = atan2(v.y, v.x);
		double halflen = len(v) / 2;
		double dth = acos(halflen / R);

		V.push_back(make_pair(dir - dth - EPS, '('));
		V.push_back(make_pair(dir + dth + EPS, ')'));
		V.push_back(make_pair(dir - dth + 2 * PI - EPS, '('));
		V.push_back(make_pair(dir + dth + 2 * PI + EPS, ')'));

	}

	sort(V.begin(), V.end());
	int best = 0, cur = 0;
	for(int i = 0; i < V.size(); i++)
	{
		if(V[i].second == '(') cur++;
		else cur--;
		best = max(best, cur);
	}
	return best;
}

/*int cnt(point o)
{
	int res = 0;
	for(int i = 0; i < N; i++)
	{
		if(len(to(o, P[i])) < R + 1e-6) res++;
	}
	return res;
}*/

int main()
{
	while(true)
	{
		cin >> N >> R;
		if(N == 0) break;
		for(int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;

		int res = 1;
		for(int i = 0; i < N; i++) res = max(res, 1 + cnt(i));
		/*for(int i = 0; i < N; i++)
			for(int j = i + 1; j < N; j++)
			{
				point s = P[i], t = P[j];
				point m = point((s.x + t.x) / 2, (s.y + t.y) / 2);
				point v = to(m, t);
				double l = len(v);
				if(l > R + 1e-6) continue;
				double d = sqrt(max(0.0, R * R - l * l));
				point c = point(-v.y / len(v), v.x / len(v));
				point o = point(m.x + c.x * d, m.y + c.y * d);
				//cout << s.x << ' ' << s.y << ' ' << t.x << ' ' << t.y << ' ' << m.x << ' ' << m.y << ' ' << v.x << ' ' << v.y << ' ' << o.x << ' ' << o.y << endl;
				res = max(res, cnt(o));
			}*/
		cout << "It is possible to cover " << res << " points.\n";
	}
}
