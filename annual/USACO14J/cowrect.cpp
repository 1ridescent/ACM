#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

int N;
vector<int> R[2][1050];

set<int> S[2];

int bit[1050];
void init()
{
	memset(bit, 0, sizeof(bit));
}
void insert(int i)
{
	for(; i < 1024; i += i & -i)
		bit[i]++;
}
int lookup(int i)
{
	int res = 0;
	for(; i > 0; i -= i & -i)
		res += bit[i];
	return res;
}

int main()
{
	freopen("cowrect.in", "r", stdin);	freopen("cowrect.out", "w", stdout);
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int x, y;
		char c;
		cin >> x >> y >> c;
		x += 3;
		y += 3;
		R[c == 'H'][x].push_back(y);
	}
	int bestnum = 0, bestarea = -1;
	for(int rmin = 0; rmin <= 1010; rmin++)
	{
		if(R[1][rmin].empty()) continue;
		S[0].clear();
		S[1].clear();
		init();
		for(int rmax = rmin; rmax <= 1010; rmax++)
		{
			for(int i = 0; i < R[0][rmax].size(); i++)
				S[0].insert(R[0][rmax][i]);
			if(R[1][rmax].empty()) continue;
			for(int i = 0; i < R[1][rmax].size(); i++)
			{
				S[1].insert(R[1][rmax][i]);
				insert(R[1][rmax][i]);
			}
			for(int i = 0; i < R[1][rmin].size(); i++)
				for(int j = (rmin == rmax ? i : 0); j < R[1][rmax].size(); j++)
				{
					int cmin = R[1][rmin][i], cmax = R[1][rmax][j];
					if(cmin > cmax) swap(cmin, cmax);
					set<int>::iterator it = S[0].lower_bound(cmin);
					if(it != S[0].end() && *it <= cmax) continue;
					int high = (it == S[0].end() ? 1007 : *it);
					int low = (it == S[0].begin() ? 1 : *(--it));
					cmin = *(S[1].upper_bound(low));
					cmax = *(--(S[1].lower_bound(high)));
					int num = lookup(cmax) - lookup(cmin - 1);
					int area = (rmax - rmin) * (cmax - cmin);
					//printf("(%d,%d) (%d,%d): num=%d area=%d bestarea=%d\n", rmin, cmin, rmax, cmax, num, area, bestarea);
					if(num > bestnum || num == bestnum && area < bestarea)
						bestnum = num, bestarea = area;
				}
		}
	}
	printf("%d\n%d\n", bestnum, bestarea);
}
