#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

set<int> used[33];

int main()
{
	int N;
	cin >> N;
	int in1, in2;
	while(cin >> in1 >> in2)
	{
		in2 *= -1;
		if(cin.peek() == '-')
		{
			// booking
			int id = in1, start = in2, num;
			cin >> num;
			num *= -1;
			//printf("id=%d start=%d num=%d\n",id,start,num);
			bool good = true;
			for(int i = start; i < start + num; i++)
				if(used[id].count(i))
					good = false;
			if(!good)
			{
				cout << "N\n";
			}
			else
			{
				cout << "Y\n";
				for(int i = start; i < start + num; i++)
				{
					//cout << "insert " << id << ' ' << i << endl;
					used[id].insert(i);
				}
			}
		}
		else
		{
			// query
			int start = in1, num = in2;
			vector<int> res;
			for(int id = 1; id <= N; id++)
			{
				bool good = true;
				for(int i = start; i < start + num; i++)
					if(used[id].count(i))
						good = false;
				if(good)
					res.push_back(id);
			}
			if(res.empty()) cout << "None\n";
			else
			{
				for(int i = 0; i < res.size(); i++)
				{
					if(i) cout << ' ';
					cout << res[i];
				}
				cout << endl;
			}
		}
	}
	return 0;
}
