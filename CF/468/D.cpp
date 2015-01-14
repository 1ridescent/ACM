#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

int N;
vector<int> G[100005];
map<int, ll> E[100005];

int size[100005];
ll depth[100005];
void get_size(int u, int p, ll d)
{
	size[u] = 1;
	depth[u] = d;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		get_size(v, u, d + E[u][v]);
		size[u] += size[v];
	}
	//cout << "size " << u << ' ' << size[u] << endl;
	//cout << "depth " << u << ' ' << d << endl;
}

int root;
void balance()
{
	get_size(1, -1, 0);
	for(int r = 2; r <= N; r++)
	{
		bool is_root = true;
		//cout << "trying " << r << endl;
		if(2 * (N - size[r]) > N) is_root = false;
		for(int i = 0; i < G[r].size(); i++)
		{
			int v = G[r][i];
			if(size[v] > size[r]) continue;
			//cout << v << " : " << size[v] << endl;
			if(2 * size[v] > N) is_root = false;
		}
		if(is_root)
		{
			//cout << "root = " << r << endl;
			root = r;
			get_size(r, -1, 0);
			return;
		}
	}
}

vector<int> accum;
void dfs(int u, int p)
{
	accum.push_back(u);
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if(v == p) continue;
		dfs(v, u);
	}
}

set<int> C[100005];
int I[200005];

map<int, set<pair<int, int> > > sizes;
set<pair<int, int> > mins;

void remove(int u)
{
	int i = I[u];
	int s = C[i].size(), m = *(C[i].begin());
	sizes[s].erase(make_pair(m, i));
	if(sizes[s].empty()) sizes.erase(s);
	mins.erase(make_pair(m, i));
	C[i].erase(u);
	//cout << "removing " << u << endl;
	if(C[i].empty()) return;

	s = C[i].size(), m = *(C[i].begin());
	sizes[s].insert(make_pair(m, i));
	mins.insert(make_pair(m, i));
	//cout << "\tnext = " << m << endl;
}

int main()
{
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		G[a].push_back(b);
		G[b].push_back(a);
		E[a][b] = E[b][a] = c;
	}
	balance();

	for(int i = 0; i < G[root].size(); i++)
	{
		int u = G[root][i];
		dfs(u, root);
		sort(accum.begin(), accum.end());
		for(int j = 0; j < accum.size(); j++)
		{
			C[i].insert(accum[j]);
			I[accum[j]] = i;
			C[i].insert(100000 + accum[j]);
			I[100000 + accum[j]] = i;
		}
		accum.clear();

		//cout << "inserting " << *(C[i].begin()) << endl;
		sizes[C[i].size()].insert(make_pair(*(C[i].begin()), i));
		mins.insert(make_pair(*(C[i].begin()), i));
	}
	C[G[root].size()].insert(root);
	I[root] = G[root].size();
	C[G[root].size()].insert(100000 + root);
	I[100000 + root] = G[root].size();
	sizes[2].insert(make_pair(root, G[root].size()));
	mins.insert(make_pair(root, G[root].size()));

	ll res = 0;
	for(int i = 1; i <= N; i++)
		res += depth[i];
	cout << 2 * res << '\n';//return 0;
	for(int u = 1; u <= N; u++)
	{
		int v = -1;
		if((--sizes.end())->first == N + 1 - u)
		{
			//cout << "crisis\n";
			int i = (--sizes.end())->second.begin()->second;
			if(i != I[u])
				v = *(C[i].begin());
		}
		if(v == -1)
		{
			set<pair<int, int> >::iterator it = mins.begin();
			if(it->second == I[u]) it++;
			v = it->first;
		}
		cout << v << ' ';
		remove(v);
		remove(100000 + u);
	}
}
