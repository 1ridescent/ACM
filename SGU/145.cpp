#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#include <map>
#include <queue>

using namespace std;

int N, M, K;
struct edge
{
	int v;
	double w;
	int id;
	edge(int v2, double w2, int id2)
	{
		v = v2, w = w2, id = id2;
	}
};
vector<edge> G[105];
map<bitset<5050>, vector<int> > paths;

void dijkstra(bitset<5050>& B)
{

}

double rand_dec()
{
	return (rand() / (double)(RAND_MAX)) * 0.001;
}

int main()
{
	cin >> N >> M >> K;
	for(int i = 0; i < M; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(edge(a, b, )
		G[b].push_back(make_pair(a, rand_dec()));
	}
}
