#include <iostream>
#include <algorithm>

using namespace std;

int R[40040];
int timestamp = 0;
struct change
{
	int t, i, v;
};
vector<change> changes;
void undo(int t)
{
	while(!changes.empty() && changes[changes.size()-1].t == t)
	{
		R[changes[changes.size()-1].i] = changes[changes.size()-1].v;
		changes.pop_back();
	}
}
void save(int i)
{
	change c;
	c.t = timestamp;
	c.i = i;
	c.v = R[i];
	changes.push_back(c);
}
void init_R()
{
    for(int i = 0; i < 40040; i++) R[i] = -1;
}
int Find(int a)
{
    if(R[a] < 0) return a;
    return Find(R[a]);
}
int Union(int a, int b)
{
    int ra = Find(a);
    int rb = Find(b);
    if(-R[ra] > -R[rb])
    {
    	save(rb);
    	R[rb] = ra;
    }
    else if(-R[ra] < -R[rb])
    {
    	save(ra);
    	R[ra] = rb;
    }
    else
    {
    	save(ra);
        R[ra] = rb;
        R[rb]--;
    }
}

struct edge
{
	int u, v, w;
};
bool cmp(edge a, edge b)
{
	return a.w < b.w;
}

int N, M;
edge E[100100];

const int mod = 1000000007;

int main()
{
	init_R();
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		cin >> E[i].u >> E[i].v >> E[i].w;
	}
	sort(E, E+M, cmp);
	int num = 1;
	int mst = 0;
	for(int i = 0; i < M; i++)
	{

	}
	return 0;
}
