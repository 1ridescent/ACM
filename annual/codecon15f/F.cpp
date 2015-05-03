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

#define SQ(x) ((x) * (x))

string name[505];

int N;
double P[505][3];
double R[505];

vector<int> G[505];

vector<int> best;

#define MAX_ITERS 10000000
int num_iters = 0;

void print();

vector<int> dfs_stack;
bool on_stack[505];
void dfs(int u)
{
	num_iters++;
	if(num_iters > MAX_ITERS) print();
	on_stack[u] = true;
	dfs_stack.push_back(u);
	if(dfs_stack.size() > best.size())
		best = dfs_stack;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		//cout << "trying " << v << endl;
		if(!on_stack[v])
			dfs(v);
	}
	on_stack[u] = false;
	dfs_stack.pop_back();
}

void print()
{vector<string> res;
for(int i = 0; i < best.size(); i++)
	res.push_back(name[best[i]]);
sort(res.begin(), res.end());
for(int i = 0; i < res.size(); i++)
{
	if(i > 0) cout << ',';
	cout << res[i];
}cout << endl;
exit(0);
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		char junk;
		cin >> P[i][0] >> junk >> P[i][1] >> junk >> P[i][2] >> junk >> R[i] >> junk >> name[i];
	}
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= N; j++)
		{
			if(j == i) continue;
			double d = 0;
			for(int k = 0; k < 3; k++)
				d += SQ(P[i][k] - P[j][k]);
			if(d < R[i] * R[i] + 1e-6)
			{
				//printf("%d->%d\n",i,j);
				G[i].push_back(j);
			}
		}
	}
	for(int i = 1; i <= N; i++)
		dfs(i);
	print();
}
