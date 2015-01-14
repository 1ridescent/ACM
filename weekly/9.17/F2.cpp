#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

// code stolen from a similar problem
struct edge {
	int x1, y1, x2, y2, id;

	/* Intuitively, this orders segments from lowest to highest.

	   For two segments such that the interval [x1, x2] intersects
	   [o.x1, o.x2], this checks if the first segment is lower than
	   the second segment at x-coordinate x in that intersection.

	   This comparison induced a total ordering on all segments which
	   will be contained in the set (below) at any given time.

	   Be careful to avoid integer overflow. */
	bool operator<(edge const& o) const {
		if (x2 < o.x2) {
			return (long long) (y2 - o.y1) * (long long) (o.x2 - o.x1) <
			       (long long) (o.y2 - o.y1) * (long long) (x2 - o.x1);
		} else {
			return (long long) (o.y2 - y1) * (long long) (x2 - x1) >
			       (long long) (y2 - y1) * (long long) (o.x2 - x1);
		}
	}
};

bool flow_left(edge e)
{
	return e.y1 < e.y2;
}

struct endpt
{
	int x, y;
	int id;
	char type;
};
bool cmp_left(endpt a, endpt b)
{
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}
bool cmp_right(endpt a, endpt b)
{
	if(a.x == b.x) return a.y < b.y;
	return a.x > b.x;
}

int N;
edge E[40040];
endpt P[80080];

set<edge> edge_set;

ll weight[40040]; // rain falls directly onto edge
vector<ll> flow_from[40040]; // u -> v : u gets flow from v

bool visited[40040];
ll total[40040];
void dfs(int u) // accumulate flows
{
	if(visited[u]) return;
	visited[u] = true;
	total[u] = weight[u];
	for(int i = 0; i < flow_from[u].size(); i++)
	{
		int v = flow_from[u][i];
		//cout << u << " -> " << v << endl;
		dfs(v);
		total[u] += total[v];
	}
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		edge e;
		cin >> e.x1 >> e.y1 >> e.x2 >> e.y2;
		e.id = i;
		E[i] = e;
		P[2 * i].x = e.x1;
		P[2 * i].y = e.y1;
		P[2 * i].id = i;
		P[2 * i].type = 'l';
		P[2 * i + 1].x = e.x2;
		P[2 * i + 1].y = e.y2;
		P[2 * i + 1].id = i;
		P[2 * i + 1].type = 'r';
	}

	memset(weight, 0, sizeof(weight));

	sort(P, P + 2 * N, cmp_left);
	for(int i = 0; i < 2 * N; )
	{
		int j = i + 1;
		while(j < 2 * N && P[j].x == P[i].x) j++;

		for(int k = i; k < j; k++)
		{
			endpt p = P[k];
			edge e = E[p.id];
			if(p.type == 'l')
			{
				edge_set.insert(e);
			}
			else
			{
				if(!flow_left(e)) // flow right onto an edge
				{
					set<edge>::iterator it = edge_set.find(e);
					if(it != edge_set.begin())
					{
						it--;
						edge e2 = *it; // e2 gets flow from e
						flow_from[e2.id].push_back(e.id);
					}
				}
			}
		}

		for(int k = i; k < j; k++)
		{
			endpt p = P[k];
			edge e = E[p.id];
			if(p.type == 'r')
			{
				edge_set.erase(e);
			}
		}

		if(!edge_set.empty())
		{
			int dx = P[j].x - P[i].x;
			edge top = *(--edge_set.end());
			weight[top.id] += dx;
		}

		i = j;
	}

	sort(P, P + 2 * N, cmp_right);
	for(int i = 0; i < 2 * N; )
	{
		int j = i + 1;
		while(j < 2 * N && P[j].x == P[i].x) j++;

		for(int k = i; k < j; k++)
		{
			endpt p = P[k];
			edge e = E[p.id];
			if(p.type == 'r')
			{
				edge_set.insert(e);
			}
			else
			{
				if(flow_left(e)) // flow right onto an edge
				{
					set<edge>::iterator it = edge_set.find(e);
					if(it != edge_set.begin())
					{
						it--;
						edge e2 = *it; // e2 gets flow from e
						flow_from[e2.id].push_back(e.id);
					}
				}
			}
		}

		for(int k = i; k < j; k++)
		{
			endpt p = P[k];
			edge e = E[p.id];
			if(p.type == 'l')
			{
				edge_set.erase(e);
			}
		}

		i = j;
	}

	memset(visited, 0, sizeof(visited));
	for(int i = 0; i < N; i++)
		if(!visited[i]) dfs(i);

	for(int i = 0; i < N; i++) cout << total[i] << '\n';

}
