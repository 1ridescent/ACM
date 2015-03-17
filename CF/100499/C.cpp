#include <bits/stdc++.h>

using namespace std;
const int inf = 1e9;

int V, H, K;
char dir[256];
int type[4] = {0, 1, 0, 1};
int up[4] = {1, 1, 0, 0};
map<int, int> remap;
int unmap[20005];
bool road[4][20005];
int next[4][2][20005];

int step(int* p, int* q, int i, int s)
{
	if(p[type[i]] == q[type[i]] && road[i][p[type[i]]] && ((p[!type[i]] > q[!type[i]]) ^ up[i]))
	{
		int res = abs(unmap[p[!type[i]]] - unmap[q[!type[i]]]);
		p[!type[i]] = q[!type[i]];
		return res;
	}
	if(!road[i][p[type[i]]]) return 0;
	//printf("go from %d %d %d %d i=%d s=%d\n",p[0],p[1],q[0],q[1],i,s);
	int j = (i + s + 4) % 4;
	int x = next[j][up[i]][p[!type[i]] + 1];
	//printf("query next[%d][%d][%d] = %d\n",j,(int)(up[i]),q[!type[i]],x);
	if(x == -1) return 0;
	//cout << "try " << p[!type[i]] << ' ' << x << ' ' << up[i] << endl;
	if(p[!type[i]] != x && !((p[!type[i]] > x) ^ up[i])) return 0;
	int res = abs(unmap[p[!type[i]]] - unmap[x]);
	p[!type[i]] = x;
	//printf("to %d %d %d %d\n",p[0],p[1],q[0],q[1]);
	return res;
}
int leap(int* p, int* q, int i, int s)
{
	if(p[type[i]] == q[type[i]] && road[i][p[type[i]]] && ((p[!type[i]] > q[!type[i]]) ^ up[i]))
	{
		int res = abs(unmap[p[!type[i]]] - unmap[q[!type[i]]]);
		p[!type[i]] = q[!type[i]];
		return res;
	}
	if(!road[i][p[type[i]]]) return 0;
	//printf("go from %d %d %d %d i=%d s=%d\n",p[0],p[1],q[0],q[1],i,s);
	int j = (i + s + 4) % 4;
	int x = next[j][up[i]][q[!type[i]]];
	//printf("query next[%d][%d][%d] = %d\n",j,(int)(up[i]),q[!type[i]],x);
	if(x == -1) return 0;
	//cout << "try " << p[!type[i]] << ' ' << x << ' ' << up[i] << endl;
	if(p[!type[i]] != x && !((p[!type[i]] > x) ^ up[i])) return 0;
	int res = abs(unmap[p[!type[i]]] - unmap[x]);
	p[!type[i]] = x;
	//printf("to %d %d %d %d\n",p[0],p[1],q[0],q[1]);
	return res;
}

void main2()
{
	int p0[2], q[2];
	cin >> p0[0] >> p0[1] >> q[0] >> q[1];
	int add = 0;
	if(p0[0] == q[0] && p0[1] == q[1])
	{
		cout << 0 << '\n';
		return;
	}
	for(int d = 0; d < 4; d++)
	{
		if(remap.count(p0[type[d]]) && road[d][remap[p0[type[d]]]] && p0[type[d]] == q[type[d]] && (p0[!type[d]] > q[!type[d]]) ^ up[d])
		{
			cout << abs(p0[!type[d]] - q[!type[d]]) << '\n';
			return;
		}
	}
	for(int d = 0; d < 4; d++)
	{
		if(remap.count(p0[type[d]]) && road[d][remap[p0[type[d]]]])
		{
			p0[type[d]] = remap[p0[type[d]]];
			map<int, int>::iterator it;
			if(up[d])
				it = remap.lower_bound(p0[!type[d]]);
			else
				it = --remap.upper_bound(p0[!type[d]]);
			add += abs(p0[!type[d]] - it->first);
			p0[!type[d]] = it->second;
			break;
		}
	}
	for(int d = 0; d < 4; d++)
	{
		if(remap.count(q[type[d]]) && road[d][remap[q[type[d]]]])
		{
			q[type[d]] = remap[q[type[d]]];
			map<int, int>::iterator it;
			if(!up[d])
				it = remap.lower_bound(q[!type[d]]);
			else
				it = --remap.upper_bound(q[!type[d]]);
			add += abs(q[!type[d]] - it->first);
			q[!type[d]] = it->second;
			break;
		}
	}
	//printf("query %d %d %d %d: ", p0[0], p0[1], q[0], q[1]);
	int res = inf;
	for(int s = -1; s <= 1; s += 2)
		for(int d = 0; abs(d) < 12; d += s)
		{
			//printf("starting from %d\n", d % 4);
			int dist = 0;
			int p[2];
			p[0] = p0[0], p[1] = p0[1];
			for(int l = 0; l < 4; l++)
				for(int i = 0; i < 8; i++)
				{
					//printf("at %d %d %d %d dist=%d\n",p[0],p[1],q[0],q[1],dist);
					if(p[0] == q[0] && p[1] == q[1])
					{
						res = min(res, dist);
						break;
					}
					if(i < l) dist += step(p, q, (d + i * s) & 3, s);
					else dist += leap(p, q, (d + i * s) & 3, s);
				}
		}
	cout << (res == inf ? -1 : res + add) << '\n';
}

int main()
{
	//ios::sync_with_stdio(false);
	dir['N'] = 0, dir['E'] = 1, dir['S'] = 2, dir['W'] = 3;
	int tests;
	cin >> tests;
	while(tests--)
	{
		cin >> V >> H >> K;
		{
			vector<int> X;
			X.push_back(0);
			for(int i = 1; i < V; i++)
			{
				int x;
				cin >> x;
				X.push_back(X.back() + x);
			}
			X.push_back(0);
			for(int i = 1; i < H; i++)
			{
				int x;
				cin >> x;
				X.push_back(X.back() + x);
			}
			string vs, hs;
			cin >> vs >> hs;
			string S = vs + hs;

			remap.clear();
			for(int i = 0; i < X.size(); i++)
				remap[X[i]] = -1;
			int id = 0;
			for(map<int, int>::iterator it = remap.begin(); it != remap.end(); it++)
			{
				it->second = id;
				unmap[id] = it->first;
				id++;
			}
			remap[inf] = id++;
			memset(road, 0, sizeof(road));
			memset(next, -1, sizeof(next));
			for(int i = 0; i < X.size(); i++)
			{
				int x = remap[X[i]], d = dir[S[i]];
				road[d][x] = true;
				next[d][0][x] = next[d][1][x] = x;
			}
			for(int d = 0; d < 4; d++)
			{
				for(int i = 1; i <= 20003; i++)
					if(next[d][0][i] == -1)
						next[d][0][i] = next[d][0][i - 1];
				for(int i = 20002; i >= 0; i--)
					if(next[d][1][i] == -1)
						next[d][1][i] = next[d][1][i + 1];
			}
		}
		while(K--)
		{
			main2();
		}
	}
}
