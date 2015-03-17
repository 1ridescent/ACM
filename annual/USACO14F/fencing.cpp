#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e15;
typedef pair<ll, ll> point;
#define x first
#define y second

point to(point u, point v)
{
	return point(v.x - u.x, v.y - u.y);
}
ll cross(point u, point v)
{
	return u.x * v.y - u.y * v.x;
}

void upper_hull(vector<point>& P, vector<point>& H)
{
	//printf("P : "); for(int i = 0; i < P.size(); i++) printf("(%d,%d) ", (int)P[i].x, (int)P[i].y); printf("\n");
	H.clear();
	for(int i = 0; i < P.size(); i++)
	{
		point p = P[i];
		while(H.size() >= 2 && cross(to(H.back(), H[H.size() - 2]), to(H.back(), p)) <= 0)
			H.pop_back();
		H.push_back(p);
	}
}

int find_tip(vector<point>& H, point v) // v must point RIGHT
{
	int low = -1, high = H.size() - 1;
	//printf("trying v=(%d,%d)",(int)v.x,(int)v.y);
	//printf("l=%d h=%d\n",low,high);
	while(low + 1 < high)
	{
		int mid = (low + high) / 2;
		if(cross(v, to(H[mid], H[mid + 1])) > 0) low = mid;
		else high = mid;
		//printf("l=%d h=%d\n",low,high);
	}
	return high;
}

int N, Q;
vector<point> P;
vector<point> H, L;
ll minX = inf, maxX = -inf;

void convex_hull()
{
	sort(P.begin(), P.end());
	upper_hull(P, H);
	for(int i = 0; i < P.size(); i++)
		P[i].x *= -1, P[i].y *= -1;
	reverse(P.begin(), P.end());
	upper_hull(P, L);
	for(int i = 0; i < P.size(); i++)
		P[i].x *= -1, P[i].y *= -1;
	for(int i = 0; i < L.size(); i++)
		L[i].x *= -1, L[i].y *= -1;
	//printf("upper hull: "); for(int i = 0; i < H.size(); i++) printf("(%d,%d) ", (int)H[i].x, (int)H[i].y); printf("\n");
	//printf("lower hull: "); for(int i = 0; i < L.size(); i++) printf("(%d,%d) ", (int)L[i].x, (int)L[i].y); printf("\n");
}

vector<point> E;

#define THR 500

int main()
{
	ios::sync_with_stdio(false);
	freopen("fencing.in", "r", stdin); freopen("fencing.out", "w", stdout);
	cin >> N >> Q;
	for(int i = 0; i < N; i++)
	{
		point p;
		cin >> p.x >> p.y;
		minX = min(minX, p.x);
		maxX = max(maxX, p.x);
		E.push_back(p);
	}
	if(E.size() >= THR)
	{
		P = E;
		convex_hull();
		E.clear();
	}
	//for(int i = 0; i < H.size(); i++) printf("(%d,%d) ", (int)H[i].x, (int)H[i].y);
	for(int q = 1; q <= Q; q++)
	{
		int t;
		cin >> t;
		if(t == 1)
		{
			point p;
			cin >> p.x >> p.y;
			minX = min(minX, p.x);
			maxX = max(maxX, p.x);
			E.push_back(p);
			if(E.size() == THR)
			{
				for(int i = 0; i < E.size(); i++)
					P.push_back(E[i]);
				convex_hull();
				E.clear();
			}
		}
		else
		{
			//cout << q << " : ";
			ll a, b, c;
			cin >> a >> b >> c;
			if(b == 0)
			{
				cout << (minX <= c && c <= maxX ? "NO\n" : "YES\n");
				continue;
			}
			point v(b, -a);
			if(v.x < 0) v.x *= -1, v.y *= -1;
			bool good = true;
			int ans = 0;
			for(int i = 0; i < E.size(); i++)
			{
				point p = E[i];
				if(a * p.x + b * p.y < c)
				{
					//cout << "- ";
					if(ans > 0) good = false;
					ans = -1;
				}
				else if(a * p.x + b * p.y > c)
				{
					//cout << "+ ";
					if(ans < 0) good = false;
					ans = 1;
				}
				else good = false;
			}
			//printf("ans = %d\n",(int)ans);
			if(!P.empty())
			{
				point p = H[find_tip(H, v)];
				//printf("tip is (%d,%d), val = %d\n",(int)p.x,(int)p.y,(int)(a*p.x+b*p.y));
				if(a * p.x + b * p.y == c) good = false;
				else if(a * p.x + b * p.y < c)
				{
					if(ans > 0) good = false;
				}
				else
				{
					v.x *= -1, v.y *= -1;
					p = L[find_tip(L, v)];
					if(a * p.x + b * p.y > c)
					{
						if(ans < 0) good = false;
					}
					else good = false;
				}
			}
			cout << (good ? "YES\n" : "NO\n");
		}
	}
}
