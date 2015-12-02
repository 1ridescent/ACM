#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>

using namespace std;

const int inf = 2.1e9;

int N, M;
int H[500005];
int min_H[500005];
vector<int> G[500005];

void make_tree(int u, int p)
{
	for(int i = 0; i < G[u].size(); i++)
		if(G[u][i] == p)
		{
			G[u].erase(G[u].begin() + i);
			break;
		}
	for(int i = 0; i < G[u].size(); i++)
	{
		//printf("%d->%d\n", u, G[u][i]);
		make_tree(G[u][i], u);
	}
}

bool is_root[500005];
int root[500005];
void find_roots(int u, int s, int r)
{
	//cout << u << ' ' << s << ' ' << H[u] << endl;
	if(H[u] < s)
	{
		is_root[u] = true;
		r = u;
	}
	s = min(s, H[u]);
	min_H[u] = s;
	root[u] = r;
	for(int i = 0; i < G[u].size(); i++)
		find_roots(G[u][i], s, r);
}

vector<pair<int, int> > group;
priority_queue<pair<int, int> > Q;
void find_group(int r)
{
	Q.push(make_pair(-inf, r));
	while(!Q.empty())
	{
		int u = Q.top().second, h = -Q.top().first;
		Q.pop();
		//cout << "u=" << u << " h=" << h << endl;
		group.push_back(make_pair(u, h));
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if(H[v] >= H[r])
				Q.push(make_pair(-min(H[v], h), v));
		}
	}
}

int K;
int miners[500005];
pair<pair<int, int>, int> heights[500005];
int used[500005]; // height of miner in cave
set<pair<int, int> > bad;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i <= N; i++)
		cin >> H[i];
	for(int i = 1; i < N; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cin >> K;
	for(int i = 1; i <= K; i++)
		cin >> miners[i];

	make_tree(1, -1);
	find_roots(1, inf, -1);

	sort(miners + 1, miners + 1 + K);
	for(int i = 1; i <= N; i++)
		heights[i] = make_pair(make_pair(min_H[i], root[i]), i);
	sort(heights + 1, heights + 1 + N);
	int p = N;
	for(int k = K; k >= 1; k--)
	{
		if(p >= 0 && heights[p].first.first >= miners[k])
		{
			used[heights[p].second] = miners[k];
			p--;
		}
		else
			bad.insert(make_pair(miners[k], k));
	}
	if(bad.empty())
	{
		cout << "0\n";
		return 0;
	}
	//cout << "bad: "; for(set<pair<int, int> >::iterator it = bad.begin(); it != bad.end(); it++) cout << it->first << ' '; cout << endl;

	int best = inf;
	for(int t = 1; t <= N; t++)
	{
		int ht = heights[t].first.first, r = heights[t].second;
		if(!is_root[r]) continue;
		//cout << "root " << r << endl;
		find_group(r);
		//cout << "group at " << r << ":"; for(int i = 0; i < group.size(); i++) cout << ' ' << group[i].first << ',' << group[i].second; cout << endl;
		if(bad.size() <= group.size()) {{{
		set<pair<int, int> > pick = bad;
		for(int i = 0; i < group.size(); i++)
			if(used[group[i].first])
				pick.insert(make_pair(ht, inf + i));
		//cout << "r=" << r << ": pick: "; for(set<pair<int, int> >::iterator it = pick.begin(); it != pick.end(); it++) cout << it->first << ' '; cout << endl;
		int val = ht;
		for(int i = 0; i < group.size(); i++)
		{
			if(i > 0)
			{
				//val = max(val, group[i].second);
				set<pair<int, int> >::iterator it = pick.upper_bound(make_pair(group[i].second + 1, -1));
				if(it != pick.begin())
				{
					it--;
					//printf("[%d]=%d erases %d\n", i, group[i].first, *it);
					val = max(val, it->first);
					pick.erase(*it);
				}
				//cout << "i=" << i << " : " << pick.size() << endl;
			}
			if(pick.size() == 1)
			{
				int h = (pick.begin())->first;
				val = max(val, h);
				best = min(best, val - ht);
				//cout << "good at " << r << ", val=" << val - ht << endl;
				break;
			}
		} }}}

		for(int i = 0; i < group.size(); i++)
		{
			if(p < N && ht >= used[heights[p + 1].second])
			{
				//cout << "recover " << heights[p + 1].second << endl;
				used[heights[p + 1].second] = 0;
				p++;
			}
		}
		//cout << "clear...\n";
		group.clear();
	}
	cout << (best == inf ? -1 : best) << endl;
}
