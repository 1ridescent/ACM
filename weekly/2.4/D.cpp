#include <bits/stdc++.h>

using namespace std;

int N, M;
map<int, pair<int, int> > D; // (left, right)

int main()
{
	cin >> N >> M;
	for(int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;
		if(x < y)
		{
			D[x].first++;
			D[y].first--;
		}
		if(x > y)
		{
			D[y].second++;
			D[x].second--;
		}
	}
	if(D.empty())
	{
		cout << M << endl;
		return 0;
	}
	long long cur_l = 0, cur_r = 0;
	long long total = 0;
	map<int, pair<int, int> >::iterator it = D.begin();
	while(it != D.end())
	{
		cur_l += it->second.first;
		cur_r += it->second.second;
		long long dist = -(it->first);
		it++;
		dist += it->first;
		//cout << dist << ' ' << cur_l << ' ' << cur_r << endl;
		total += (max(cur_l - 1, cur_r) * dist * 2);
	}
	cout << M + total << endl;
}
