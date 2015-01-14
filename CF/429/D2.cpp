#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <map>
#include <ctime>

using namespace std;

typedef long long ll;

class Point
{
public:
	ll x, y;
	Point() { }
	Point(ll x2, ll y2)
	{
		x = x2, y = y2;
	}
	ll sqlength()
	{
		return x * x + y * y;
	}
	Point operator+(Point p)
	{
		return Point(x + p.x, y + p.y);
	}
	Point operator-(Point p)
	{
		return Point(x - p.x, y - p.y);
	}
	Point operator*(ll s)
	{
		return Point(s * x, s * y);
	}
};

vector<int> RandomPerm(int n)
{
	vector<int> V;
	vector<bool> used(n);
	for(int i = 0; i < n; i++) used[i] = false;
	while(V.size() < n)
	{
		int next = rand() % n;
		if(used[next]) continue;
		V.push_back(next);
		used[next] = true;
	}
	return V;
}

const double EPS = 1e-8;
ll ClosestPair(vector<Point> P)
{
	vector<int> perm = RandomPerm(P.size());
	ll sqdist = (P[0] - P[1]).sqlength();

	while(true)
	{
		bool restart = false;
		double alpha = sqrt(sqdist) / 2.0;

		map<pair<int, int>, int> hash;
		for(int i = 0; i < P.size(); i++)
		{
			Point next = P[perm[i]];
			int hx = next.x / alpha, hy = next.y / alpha;
			if(hash.find(make_pair(hx, hy)) != hash.end()) // found point too close
			{
				sqdist = (next - P[hash[make_pair(hx, hy)]]).sqlength();
				restart = true;
			}
			for(int dx = -2; dx <= 2; dx++)
				for(int dy = -2; dy <= 2; dy++)
					if(hash.find(make_pair(hx + dx, hy + dy)) != hash.end())
					{
						double newsqdist = (next - P[hash[make_pair(hx + dx, hy + dy)]]).sqlength();
						if(newsqdist < sqdist)
						{
							sqdist = newsqdist;
							restart = true;
						}
					}
			if(restart) break;
			hash[make_pair(hx, hy)] = perm[i];
		}

		if(restart) continue;
		return sqdist;
	}
}

int main()
{
	srand(time(0));
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<Point> P;
	ll cumul = (1LL << 37);
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		cumul += x;
		P.push_back(Point(i, cumul));
	}
	cout << ClosestPair(P) << endl;
	return 0;
}
