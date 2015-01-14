#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> point;
#define x first
#define y second

int N;

point P[1050];
vector<int> H[20050];
vector<int> V[20050];

map<point, point> hor, ver;

int main()
{
	while(true)
	{
		for(int i = 0; i < 20050; i++)
		{
			H[i].clear();
			V[i].clear();
		}
		hor.clear();
		ver.clear();

		cin >> N;
		if(!N) break;
		for(int i = 1; i <= N; i++)
		{
			int x, y;
			cin >> x >> y;
			x += 10005;
			y += 10005;
			P[i] = point(x, y);
			H[y].push_back(x);
			V[x].push_back(y);
		}

		for(int i = 0; i < 20050; i++)
		{
			sort(V[i].begin(), V[i].end());
			sort(H[i].begin(), H[i].end());
		}

		for(int y = 0; y < 20050; y++)
		{
			for(int i = 0; i < H[y].size(); i += 2)
			{
				int x1 = H[y][i];
				int x2 = H[y][i + 1];
				hor[point(x1, y)] = point(x2, y);
				hor[point(x2, y)] = point(x1, y);
			}
		}
		for(int x = 0; x < 20050; x++)
		{
			for(int i = 0; i < V[x].size(); i += 2)
			{
				int y1 = V[x][i];
				int y2 = V[x][i + 1];
				ver[point(x, y1)] = point(x, y2);
				ver[point(x, y2)] = point(x, y1);
			}
		}

		point s = P[1];
		for(int i = 1; i <= N; i++)
			if(P[i] < s)
				s = P[i];

		char next = 'v';
		bool start = false;
		while(true)
		{
			if(s.x == P[1].x && s.y == P[1].y)
			{
				if(start) break;
				start = true;
			}

			point t;

			if(next == 'v')
			{
				t = ver[s];
				if(start)
				{
					if(t.y > s.y) cout << 'N';
					else cout << 'S';
				}
				next = 'h';
			}
			else
			{
				t = hor[s];
				if(start)
				{
					if(t.x > s.x) cout << 'E';
					else cout << 'W';
				}
				next = 'v';
			}
			s = t;
		}
		cout << '\n';
	}
}
