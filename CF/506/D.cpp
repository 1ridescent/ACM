#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>

using namespace std;

int N, M, K;
map<int, vector<int> > C[100005];
map<pair<int, int>, int> Qmap;
pair<int, int> Qlist[100005];
int ans[100005];
int dupe[100005];

vector<int> cur;
set<int> vis;
void dfs(int c, int u)
{
	cur.push_back(u);
	vis.insert(u);
	for(int i = 0; i < C[c][u].size(); i++)
	{
		int v = C[c][u][i];
		if(!vis.count(v)) dfs(c, v);
	}
}
bool vis2[100005];
void process()
{
	//cout << "cur: "; for(int i = 0; i < cur.size(); i++) cout << cur[i] << ' '; cout << endl;
	if(cur.size() <= 300)
	{
		for(int i = 0; i < cur.size(); i++)
			for(int j = i + 1; j < cur.size(); j++)
			{
				//cout << "trying" << cur[i] << ' ' << cur[j] << endl;
				map<pair<int, int>, int>::iterator it = Qmap.find(make_pair(cur[i], cur[j]));
				if(it != Qmap.end())
				{
					//cout << it->second << endl;
					ans[it->second]++;
				}
			}
	}
	else
	{
		memset(vis2, 0, sizeof(vis2));
		for(int i = 0; i < cur.size(); i++)
			vis2[cur[i]] = true;
		for(int i = 0; i < K; i++)
		{
			int a = Qlist[i].first, b = Qlist[i].second;
			if(vis2[a] && vis2[b])
				ans[i]++;
		}
	}
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		C[c][a].push_back(b);
		C[c][b].push_back(a);
	}
	memset(dupe, -1, sizeof(dupe));
	cin >> K;
	for(int i = 0; i < K; i++)
	{
		int a, b;
		cin >> a >> b;
		Qlist[i] = make_pair(a, b);
		if(Qmap.count(make_pair(a, b)))
		{
			dupe[i] = Qmap[make_pair(a, b)];
			//cout << "dupe " << i << ' ' << dupe[i] << endl;
		}
		else
		{
			Qmap[make_pair(a, b)] = i;
			Qmap[make_pair(b, a)] = i;
		}
	}
	for(int c = 1; c <= M; c++)
	{
		vis.clear();
		for(map<int, vector<int> >::iterator it = C[c].begin(); it != C[c].end(); it++)
		{
			int u = it->first;
			if(!vis.count(u))
			{
				dfs(c, u);
				process();
			}
			cur.clear();
		}
	}
	for(int i = 0; i < K; i++)
		cout << (dupe[i] != -1 ? ans[dupe[i]] : ans[i]) << '\n';
}
