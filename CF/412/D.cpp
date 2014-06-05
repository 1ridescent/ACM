#include <iostream>
#include <queue>
#include <set>

using namespace std;

int N, M;
set<pair<int, int> > E;
int P[100100];
int loc[100100];
#define CONT(S, v) ((S).find(v) != (S).end())

queue<pair<int, int> > Q;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 0; i < M; i++)
	{
		pair<int, int> e;
		cin >> e.first >> e.second;
		E.insert(e);
	}
	for(int i = 1; i <= N; i++) P[i] = loc[i] = i;
	for(int i = 1; i <= N - 1; i++)
	{
		if(CONT(E, make_pair(i, i + 1))) Q.push(make_pair(i, i + 1));
	}
	while(!Q.empty())
	{
		int u = Q.front().first, v = Q.front().second;
		Q.pop();
		int lu = loc[u], lv = loc[v];
		if(lu + 1 != lv) continue;
		swap(P[lu], P[lv]);
		swap(loc[u], loc[v]);
		if(lu > 1 && CONT(E, make_pair(P[lu - 1], P[lu]))) Q.push(make_pair(P[lu - 1], P[lu]));
		if(lu < N && CONT(E, make_pair(P[lu], P[lu + 1]))) Q.push(make_pair(P[lu], P[lu + 1]));
		if(lv > 1 && CONT(E, make_pair(P[lv - 1], P[lv]))) Q.push(make_pair(P[lv - 1], P[lv]));
		if(lv < N && CONT(E, make_pair(P[lv], P[lv + 1]))) Q.push(make_pair(P[lv], P[lv + 1]));
	}
	for(int i = 1; i <= N; i++) cout << P[i] << (i == N ? '\n' : ' ');
	return 0;
}