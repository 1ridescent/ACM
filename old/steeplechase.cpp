#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;
const ll inf = 1e13;

int s = 1007, t = 1008;
vector<int> G[1010];
vector<int> G2[1010];
ll C[1010][1010];
int from[1010];

ll augment_path()
{
    for(int i=0;i<1010;i++) from[i] = -1;
    queue<int> Q;
    from[s] = 0;
    Q.push(s);
    while(!Q.empty())
    {
        int u = Q.front();

    	//cout << "at   ' " << u <<endl;
        Q.pop();
        if(u == t) // found an augmenting path
        {
            ll flow = inf;
            int v = t;
            while(v != s)
            {
                u = from[v];
                flow = min(flow, C[u][v]);
                v = u;
            }
            v = t;
            while(v != s)
            {
                u = from[v];
                C[u][v] -= flow;
                C[v][u] += flow;
                v = u;
            }
            return flow;
        }
        for(int i=0;i<G[u].size();i++)
        {
            int v = G[u][i];
            //cout << u << "->"<< v << endl;
            //cout << "c_uv="<<C[u][v] << endl;
            if(from[v] != -1) continue; // already visited
            if(C[u][v] == 0) continue; // can't flow
            from[v] = u;
            Q.push(v);
            //cout << "pushed" << v << endl;
        }
    }
    return 0;
}

void add_edge(int u, int v, int c)
{
	//cout << u << "-->" << v << endl;
    G[u].push_back(v);
    G[v].push_back(u);
    C[u][v] = c;
    C[v][u] = 0;
}

struct hseg
{
	int y, l, r;
};
struct vseg
{
	int x, u, d;
};
bool intersects(hseg h, vseg v)
{
	return (h.l <= v.x && v.x <= h.r && v.d <= h.y && h.y <= v.u);
}

int N;
vector<hseg> H;
vector<vseg> V;

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int xl, xr, yd, yu;
		cin >> xl >> yd >> xr >> yu;
		if(xl > xr) swap(xl, xr);
		if(yd > yu) swap(yd, yu);
		if(xl == xr)
		{
			vseg v;
			v.x = xl, v.d = yd, v.u = yu;
			V.push_back(v);
		}
		else
		{
			hseg h;
			h.y = yd, h.l = xl, h.r = xr;
			H.push_back(h);
		}
	}
    ll total = 0;
    for(int i = 0; i < H.size(); i++)
    {
    	add_edge(s, i, 1);
    }
    for(int i = 0; i < V.size(); i++)
    {
    	add_edge(500+i, t, 1);
    }
    for(int h = 0; h < H.size(); h++)
    	for(int v = 0; v < V.size(); v++)
    	{
    		if(intersects(H[h], V[v]))
    		{
    			add_edge(h, 500+v, 1000);
    		}
    	}
    ll flow = 0, add;
    do
    {
        add = augment_path();
        flow += add;
    }
    while(add > 0);
    cout << N - flow << endl;
    return 0;
}
