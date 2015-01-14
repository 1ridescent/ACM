#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

struct point
{
	int x, y;
};
bool cmp(point a, point b)
{
	return a.x + a.y < b.x + b.y;
}

int N;
point P[10010];
map<int, map<int, int> > X, Y;
int H[10010], V[10010];

struct seg
{
	char t;
	int x, y, yl, yr;
};
bool cmpseg(seg a, seg b)
{
	return a.x < b.x;
}
vector<seg> S;

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		cin >> P[i].x >> P[i].y;
	}
	sort(P, P + N, cmp);
	for(int i = 0; i < N; i++)
	{
		X[P[i].x][P[i].y] = Y[P[i].y][P[i].x] = i;
	}
	for(int i = 0; i < N; i++) H[i] = V[i] = -1;
	for(int i = 0; i < N; i++)
	{
		if(H[i] == -1)
		{
			map<int, int>::iterator it = Y[P[i].y].upper_bound(P[i].x);
			if(it == Y[P[i].y].end())
			{
				cout << 0 << endl;
				return 0;
			}
			H[i] = it->second;
			H[it->second] = i;
		}
		if(V[i] == -1)
		{
			map<int, int>::iterator it = X[P[i].x].upper_bound(P[i].y);
			if(it == X[P[i].x].end())
			{
				cout << 0 << endl;
				return 0;
			}
			V[i] = it->second;
			V[it->second] = i;
		}
	}

	int len = 0;
	for(int i = 0; i < N; i++)
	{
		if(P[i].y < P[V[i]].y)
		{
			len += P[V[i]].y - P[i].y;
			seg s;
			s.t = 'v';
			s.x = P[i].x;
			s.yl = P[i].y;
			s.yr = P[V[i]].y;
			S.push_back(s);
		}
		if(P[i].x < P[H[i]].x)
		{
			len += P[H[i]].x - P[i].x;
			seg s;
			s.t = 'l';
			s.x = P[i].x;
			s.y = P[i].y;
			S.push_back(s);
			s.t = 'r';
			s.x = P[H[i]].x;
			assert(s.y == P[H[i]].y);
			S.push_back(s);
		}
	}
	sort(S.begin(), S.end(), cmpseg);
	set<int> cur_y;
	for(int i = 0; i < S.size(); i++)
	{
		seg& s = S[i];
		if(s.t == 'l') cur_y.insert(s.y);
		if(s.t == 'r') cur_y.erase(s.y);
		if(s.t == 'v')
		{
			if(cur_y.lower_bound(s.yl) != cur_y.lower_bound(s.yr))
			{
				cout << 0 << endl;
				return 0;
			}
		}
	}

	int i = 0, cnt = 0, cur = 'h';
	do
	{
		if(cur == 'h')
		{
			i = H[i];
			cur = 'v';
		}
		else
		{
			i = V[i];
			cur = 'h';
		}
		cnt++;
	}
	while(i != 0);
	if(cnt != N)
	{
		cout << 0 << endl;
		return 0;
	}

	cout << len << endl;
	return 0;
}
