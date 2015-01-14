#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

map<int, vector<int> > hor, ver;

set<int> xline, yline;

set<pair<int, int> > see;

int N, M;

pair<bool, int> before(set<int>& S, int x)
{
	set<int>::iterator it = S.lower_bound(x);
	if(it == S.begin()) return make_pair(false, 0);
	it--;
	return make_pair(true, *it);
}
pair<bool, int> after(set<int>& S, int x)
{
	set<int>::iterator it = S.upper_bound(x);
	if(it == S.end()) return make_pair(false, 0);
	return make_pair(true, *it);
}

int main2()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	if(!N && !M) return 0;
	for(int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;
		hor[y].push_back(x);
		ver[x].push_back(y);
	}
	for(int i = 0; i < M; i++)
	{
		char c, j;
		cin >> c >> j;
		if(c == 'x')
		{
			int x;
			cin >> x;
			xline.insert(x);
		}
		else
		{
			int y;
			cin >> y;
			yline.insert(y);
		}
	}
	for(map<int, vector<int> >::iterator it = hor.begin(); it != hor.end(); it++)
	{
		vector<int>& V = it->second;
		sort(V.begin(), V.end());

		int y = it->first;
		{ // check first
			int x = V.front();
			pair<bool, int> bf = before(xline, x);
			if(bf.first) see.insert(make_pair(x, y));
		}
		{ // check last
			int x = V.back();
			pair<bool, int> af = after(xline, x);
			if(af.first) see.insert(make_pair(x, y));
		}
		for(int i = 0; i < V.size() - 1; i++)
		{
			int x1 = V[i], x2 = V[i + 1];
			pair<bool, int> bf = after(xline, x1);
			if(bf.first && bf.second < x2)
			{
				see.insert(make_pair(x1, y));
				see.insert(make_pair(x2, y));
			}
		}
	}

	for(map<int, vector<int> >::iterator it = ver.begin(); it != ver.end(); it++)
	{
		vector<int>& V = it->second;
		sort(V.begin(), V.end());

		int x = it->first;
		{ // check first
			int y = V.front();
			pair<bool, int> bf = before(yline, y);
			if(bf.first) see.insert(make_pair(x, y));
		}
		{ // check last
			int y = V.back();
			pair<bool, int> af = after(yline, y);
			if(af.first) see.insert(make_pair(x, y));
		}
		for(int i = 0; i < V.size() - 1; i++)
		{
			int y1 = V[i], y2 = V[i + 1];
			pair<bool, int> bf = after(yline, y1);
			if(bf.first && bf.second < y2)
			{
				see.insert(make_pair(x, y1));
				see.insert(make_pair(x, y2));
			}
		}
	}
	cout << see.size() << '\n';
	return 1;
}

int main()
{
	while(main2())
	{
		hor.clear();
		ver.clear();
		xline.clear();
		yline.clear();
		see.clear();
	}
}
