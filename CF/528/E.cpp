#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef complex<ld> point;
#define X real()
#define Y imag()

const ld R = 2e6;
ld angle(point u, point v)
{
	ld res = arg(v) - arg(u);
	if(res < 0) res += 2 * M_PI;
	return res;
}
ld area(point a, point b, point c)
{
	ld x = a.X * b.Y + b.X * c.Y + c.X * a.Y;
	ld y = a.Y * b.X + b.Y * c.X + c.Y * a.X;
	return abs((x - y) / 2.0);
}

typedef pair<point, point> line;
#define s first
#define t second
line to_line(int a, int b, int c)
{
	point u, v;
	if(a != 0)
	{
		u = point(((ld)c - b * 0) / a, 0);
		v = point(((ld)c - b * 1) / a, 1);
	}
	else
	{
		u = point(0, ((ld)c - a * 0) / b);
		v = point(1, ((ld)c - a * 1) / b);
	}
	if(arg(v - u) < 0) swap(u, v);
	return line(u, v);
}
ld dir(line l)
{
	point u = l.t - l.s;
	ld res = arg(u);
	if(res < 0) res += M_PI;
	return res;
}
bool cmp(line a, line b)
{
	return dir(a) < dir(b);
}

pair<point, point> ends(line l)
{
	ld x = l.s.X, y = l.s.Y;
	point r = l.t - l.s;
	ld u = r.X, v = r.Y;
	ld a = (u * u + v * v);
	ld b = (2 * x * u + 2 * y * v);
	ld c = (x * x + y * y - R * R);
	ld t1 = -b / (2 * a);
	ld t2 = sqrt(b * b - 4 * a * c) / (2 * a);
	return make_pair(l.s + (t1 + t2) * r, l.s + (t1 - t2) * r);
}
point intersect(line l1, line l2)
{
	point p1 = l1.s, p2 = l2.s;
	point r1 = l1.t - l1.s, r2 = l2.t - l2.s;
	ld x1 = p1.X, y1 = p1.Y, x2 = p2.X, y2 = p2.Y;
	ld u1 = r1.X, v1 = r1.Y, u2 = r2.X, v2 = r2.Y;
	ld t1 = ((x2 - x1) * v2 - (y2 - y1) * u2) / (u1 * v2 - v1 * u2);
	return p1 + t1 * r1;
}
ld sector(point p, point s, point t)
{
	ld a = arg(t) - arg(s);
	while(a < -M_PI) a += 2 * M_PI;
	while(a > M_PI) a -= 2 * M_PI;
	a = abs(a);
	//cout << s.X << ' ' << s.Y << ' ' << t.X << ' ' << t.Y << ' ' << arg(s) << ' ' << arg(t) << ' ' << a << endl;
	return area(p, s, t) + (a / 2.0 * R * R - area(point(0, 0), s, t));
}

int N;
line L[3005];
point S[3005], T[3005];
point E[3005][2];

int main()
{
	//int a,b,c;cin>>a>>b>>c;point p=ends(to_line(a,b,c)).s;cout<<p.X<<' '<<p.Y<<endl;return 0;
	//int a,b,c,d,e,f;cin>>a>>b>>c>>d>>e>>f;point p=intersect(to_line(a,b,c),to_line(d,e,f));cout<<p.X<<' ' <<p.Y<<endl;return 0;
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		L[i] = to_line(a, b, c);
	}
	sort(L, L + N, cmp);
	for(int i = 0; i < N; i++)
	{
		pair<point, point> e = ends(L[i]);
		E[i][0] = e.first, E[i][1] = e.second;
	}
	ld num = (ld)N * (N - 1) * (N - 2) / 6.0;
	ld outside = 0;
	for(int s = 0; s < N; s++)
	{
		for(int t = s + 1; t < N; t++)
		{
			point p = intersect(L[s], L[t]);
			ld a = (t - s - 1) * (sector(p, E[s][0], E[t][0]) + sector(p, E[s][1], E[t][1]));
			ld b = (s + N - t - 1) * (sector(p, E[s][0], E[t][1]) + sector(p, E[s][1], E[t][0]));
			//cout << s << ' ' << t << ' ' << a << ' ' << b << endl;
			outside += a + b;
		}
	}
	//cout << outside << endl;
	printf("%.9f\n", (double)(M_PI * R * R - outside / num / 2.0));
}
