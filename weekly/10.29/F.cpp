#include <iostream>
#include <algorithm>
#include <set>
#include <deque>

using namespace std;

typedef long long ll;

typedef pair<ll, ll> point;
#define x first
#define y second

inline ll sqdist(point p, point q)
{
	return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}

set<point> Y;

inline point rev(point p)
{
	return point(p.y, p.x);
}


int N;
ll K;
point P[100100];

int main()
{
	ios::sync_with_stdio(false);
	while(true)
	{
		Y.clear();

		cin >> N >> K;
		if(!N) break;
		for(int i = 0; i < N; i++)
		{
			cin >> P[i].x >> P[i].y;
		}
		sort(P, P + N);

		ll cnt = 0;
		int back = 0;
		for(int i = 0; i < N; i++)
		{
			while(back < N && P[i].x - P[back].x > K)
			{
				Y.insert(rev(P[back]));
				back++;
			}
			set<point>::iterator it = Y.lower_bound(rev(P[i]));
			for(set<point>::iterator it2 = it; it2 != Y.end() && it2->first <= P[i].y + K; it2++)
			{
				if(sqdist(*it2, P[i]) <= K * K) cnt++;
			}
			if(it == Y.begin()) continue;
			for(it--; it->first >= P[i].y - K; it--)
			{
				if(sqdist(*it, P[i]) <= K * K) cnt++;
				if(it == Y.begin()) break;
			}
		}

		cout << cnt << '\n';
	}
}
