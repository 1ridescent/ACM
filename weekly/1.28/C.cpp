#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int N;

set<pair<int, int> > V, P;
set<pair<int, int> > vis;

vector<pair<int, int> > stk;

int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;
		P.insert(make_pair(x, y));
		for(int dx = -1; dx <= 1; dx++)
			for(int dy = -1; dy <= 1; dy++)
				V.insert(make_pair(x + dx, y + dy));
	}
	int x0 = V.begin()->first, y0 = V.begin()->second;
	stk.push_back(make_pair(x0, y0));
	vis.insert(make_pair(x0, y0));
	int ans = 0;
	while(!stk.empty())
	{
		x0 = stk.back().first, y0 = stk.back().second;
		//cout << " at " << x0 << ' ' << y0 << endl;
		stk.pop_back();
		for(int i = 0; i < 4; i++)
		{
			int dx = dir[i][0], dy = dir[i][1];
			int x = x0 + dx, y = y0 + dy;
			if(!V.count(make_pair(x, y)) || vis.count(make_pair(x, y))) continue;
			if(P.count(make_pair(x, y)))
			{
				ans++;
				continue;
			}
			stk.push_back(make_pair(x, y));
			vis.insert(make_pair(x, y));
		}
	}
	cout << ans << endl;
}
