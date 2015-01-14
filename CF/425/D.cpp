#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define THR 300

typedef long long point;
#define x(p) ((p) / 1000000)
#define y(p) ((p) % 1000000)
#define point(x, y) (1000000LL * (x) + (y))

int N;
vector<point> P;
unordered_set<point> S;

inline bool has(int x, int y)
{
	return (S.find( point(x, y) ) != S.end());
}
inline bool exists(int x, int y, int len)
{
	//cout << x << ' ' << y << ' ' << len << endl;
	return has(x, y) && has(x + len, y) && has(x, y + len) && has(x + len, y + len);
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;
		P.push_back( point(x, y) );
		S.insert( point(x, y) );
	}
	sort(P.begin(), P.end());

	int cnt = 0;
	for(int l = 0; l < P.size(); )
	{
		int r = l + 1;
		while(r < P.size() && x(P[l]) == x(P[r])) r++;

		//for(int i = l; i < r; i++) cout << P[i].x << ',' << P[i].y << ' ';

		if(r - l <= THR)
		{
			for(int i = l; i < r; i++)
				for(int j = i + 1; j < r; j++)
				{
					int len = y(P[j]) - y(P[i]);
					if(exists(x(P[i]) - len, y(P[i]), len)) cnt++;
				}
		}
		else
		{
			unordered_set<int> Y;
			for(int i = l; i < r; i++) Y.insert(y(P[i]));

			for(int i = 0; i < l; i++)
			{
				if(Y.find(y(P[i])) != Y.end())
				{
					int len = x(P[l]) - x(P[i]);
					if(exists(x(P[i]), y(P[i]), len)) cnt++;
				}
			}
		}

		l = r;
	}
	cout << cnt << endl;
	return 0;
}
