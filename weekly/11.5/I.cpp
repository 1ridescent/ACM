#include <iostream>
#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;
#define x first
#define y second

ll gcd(ll x, ll y)
{
	if(y == 0) return x;
	return gcd(y, x % y);
}
point normalize(point v)
{
	if(v.x < 0)
	{
		v.x *= -1;
		v.y *= -1;
	}
	ll g = gcd(v.x, abs(v.y));
	v.x /= g;
	v.y /= g;
	if(v.x == 0) v.y = abs(v.y);
	return v;
}
point perp(point v)
{
	return normalize(point(-v.y, v.x));
}

point mult(ll a, ll b, point p)
{
	return point(a * p.x + b * p.y, -b * p.x + a * p.y);
}

int N;
map<point, vector<point> > M;

map<ll, ll> D;
ll compute(vector<ll>& X, vector<ll>& Y)
{
	D.clear();
	for(int i = 0; i < X.size(); i++)
		for(int j = i + 1; j < X.size(); j++)
			D[abs(X[j] - X[i])]++;
	ll res = 0;
	for(int i = 0; i < Y.size(); i++)
		for(int j = i + 1; j < Y.size(); j++)
			res += D[abs(Y[j] - Y[i])];
	return res;
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		point s, t;
		cin >> s.x >> s.y >> t.x >> t.y;
		point v = point(t.x - s.x, t.y - s.y);
		v = normalize(v);
		//cout << s.first << ' ' << s.second << ',' << v.first << ',' << v.second << endl;
		M[v].push_back(s);
	}
	ll total = 0;
	for(map<point, vector<point> >::iterator it = M.begin(); it != M.end(); it++)
	{
		point u = it->first;
		point v = perp(u);
		//cout << " at " << u.x << ' ' << u.y << ":\n";
		vector<ll> X, Y;
		for(int i = 0; i < M[u].size(); i++)
		{
			point p = M[u][i];
			p = mult(u.x, u.y, p);
			//cout << M[u][i].x << ' ' << M[u][i].y << " -> " << p.x << ' ' << p.y << endl;
			X.push_back(p.y);
		}
		//cout << "---\n";
		for(int i = 0; i < M[v].size(); i++)
		{
			point p = M[v][i];
			p = mult(u.x, u.y, p);
			//cout << M[v][i].x << ' ' << M[v][i].y << " -> " << p.x << ' ' << p.y << endl;
			Y.push_back(p.x);
		}
		total += compute(X, Y);
	}
	cout << total / 2 << endl;
	return 0;
}
