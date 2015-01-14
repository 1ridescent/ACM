#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int inf = 2e9;
const double eps = 1e-9;

typedef pair<int, int> point;
#define x first
#define y second

int N;
point P[55];

int ymin, ymax;

map<int, int> X0, X1;

vector<int> res1, res2, res3;

int main()
{
	ios::sync_with_stdio(false);
	int P1;cin >> P1;for(int P2=1;P2<=P1;P2++){

		cin >> N;
		for(int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;

		ymin = ymax = P[0].y;
		for(int i = 0; i < N; i++)
		{
			ymin = min(ymin, P[i].y);
			ymax = max(ymax, P[i].y);
		}

		X0.clear();
		X1.clear();

		int p = 0;
		while(P[(p + 1) % N].y == ymax) p++;
		for(; P[p].y != ymin; p = (p + 1) % N)
		{
			int q = (p + 1) % N;
			ll x1 = P[p].x, y1 = P[p].y;
			ll x2 = P[q].x, y2 = P[q].y;
			X1[y1] = x1 - 1;
			X1[y2] = x2 - 1;
			for(ll y = y1 - 1; y > y2; y--)
			{
				ll x = x1 + ((x2 - x1) * (y - y1) - 1 + inf * (y1 - y2)) / (y1 - y2) - inf;
				X1[y] = x;
			}
		}

		while(P[(p + 1) % N].y == ymin) p++;
		for(; P[p].y != ymax; p = (p + 1) % N)
		{
			int q = (p + 1) % N;
			ll x1 = P[p].x, y1 = P[p].y;
			ll x2 = P[q].x, y2 = P[q].y;
			X0[y1] = x1 + 1;
			X0[y2] = x2 + 1;
			for(ll y = y1 + 1; y < y2; y++)
			{
				ll x = x1 + ((x2 - x1) * (y - y1) + (y2 - y1) + inf * (y2 - y1)) / (y2 - y1) - inf;
				X0[y] = x;
			}
		}

		res1.clear(); res2.clear(); res3.clear();
		for(int y = ymax; y >= ymin; y--)
		{
			int x1 = X0[y], x2 = X1[y];
			if(x1 <= x2)
			{
				res1.push_back(y); res2.push_back(x1); res3.push_back(x2);
			}
		}
		cout << P2 << ' ' << res1.size() << '\n';
		for(int i = 0; i < res1.size(); i++)
			cout << res1[i] << ' ' << res2[i] << ' ' << res3[i] << '\n';
	}
}
