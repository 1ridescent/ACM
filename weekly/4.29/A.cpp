#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;
#define x first
#define y second

ll dist(point a, point b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

int N;
point P[100005];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> P[i].x >> P[i].y;
	ll sum = 0, best = 0;
	for(int i = 2; i <= N; i++) sum += dist(P[i - 1], P[i]);
	for(int i = 2; i <= N - 1; i++)
		best = max(best, dist(P[i - 1], P[i]) + dist(P[i], P[i + 1]) - dist(P[i - 1], P[i + 1]));
	cout << sum - best << endl;
}
