#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <set>

using namespace std;

typedef long long ll;

typedef pair<ll, pair<ll, ll> > point;

const ll offset = 2000000005;

#define x first
#define y second.first
#define z second.second
#define make_triple(x, y, z) make_pair(x, make_pair(y, z))

inline ll sqdist(point p, point q)
{
	return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y) + (p.z - q.z) * (p.z - q.z);
}

int N;
ll K;
map<point, vector<point> > M;
set<pair<point, point> > S;

int main()
{
	ios::sync_with_stdio(false);
	while(true)
	{
		M.clear();
		cin >> N >> K;
		if(!N) break;
		ll t = K + 1;
		S.clear();

		for(int i = 0; i < N; i++)
		{
			point p;
			cin >> p.x >> p.y >> p.z;
			p.x += offset; p.y += offset; p.z += offset;
			for(int dx = -1; dx <= 1; dx++)
				for(int dy = -1; dy <= 1; dy++)
					for(int dz = -1; dz <= 1; dz++)
						M[make_triple(p.x / t + dx, p.y / t + dy, p.z / t + dz)].push_back(p);
		}
		for(map<point, vector<point> >::iterator it = M.begin(); it != M.end(); it++)
		{
			for(int i = 0; i < it->second.size(); i++)
			{
				for(int j = i + 1; j < it->second.size(); j++)
				{
					if(sqdist(it->second[i], it->second[j]) < K * K)
					{
						S.insert(make_pair(it->second[i], it->second[j]));
						S.insert(make_pair(it->second[j], it->second[i]));
					}
				}
			}
		}
		/*for(set<pair<point, point> >::iterator it = S.begin(); it != S.end(); it++)
		{
			cout << it->first.x << ' ' << it->first.y << ' ' << it->first.z << ' ' << it->second.x << ' ' << it->second.y << ' ' << it->second.z << " : " << sqdist(it->first, it->second) << endl;
		}*/
		cout << S.size() / 2 << '\n';
	}
}
