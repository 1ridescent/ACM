#include <bits/stdc++.h>

using namespace std;

int M, K;
int cur[100005];
set<pair<int, int> > cur_set;
struct event
{
	int k, b;
};
event events[100005];
int low[100005];
bool ans[100005];
int unknown;
bool found;

void clean()
{
	while(!cur_set.empty() && (cur_set.begin())->first <= unknown)
	{
		ans[(cur_set.begin())->second] = true;
		cur_set.erase(cur_set.begin());
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--)
	{
		cin >> M >> K;
		M--;
		cur_set.clear();
		for(int i = 1; i <= K; i++)
		{
			cin >> cur[i];
			low[i] = 0;
			ans[i] = false;
		}
		unknown = 0;
		found = false;
		for(int i = 1; i <= M; i++)
		{
			cin >> events[i].k >> events[i].b;
			low[events[i].k]++;
		}
		for(int i = 1; i <= K; i++)
			if(low[i] == 0)
				cur_set.insert(make_pair(cur[i], i));
		for(int i = 1; i <= M; i++)
		{
			if(events[i].b && !found)
			{
				int s = (cur_set.begin())->first;
				int k = (cur_set.begin())->second;
				assert(s <= unknown);
				//cout << "used "<< s << ' ' <<k << endl;
				clean();
				unknown -= s;
				found = true;
			}
			int k = events[i].k;
			if(k == 0) unknown++;
			else
			{
				low[k]--;
				if(low[k] == 0)
					cur_set.insert(make_pair(cur[k], k));
				if(cur_set.count(make_pair(cur[k], k)))
				{
					cur_set.erase(make_pair(cur[k], k));
					cur[k]--;
					cur_set.insert(make_pair(cur[k], k));
				}
				else cur[k]--;
				if(cur[k] == 0)
				{
					found = true;
					ans[k] = true;
					cur_set.erase(make_pair(cur[k], k));
				}
			}
		}
		clean();
		for(int i = 1; i <= K; i++)
			cout << (ans[i] ? 'Y' : 'N');
		cout << '\n';
	}
}
