#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAX = (1 << 17);

	int R[MAX];
	void init()
	{
		for(int i = 0; i < MAX; i++) R[i] = -1;
	}
	int find(int v)
	{
		if(R[v] < 0) return v;
		return find(R[v]);
	}
	void uni(int u, int v)
	{
		//cout << "unioning " << u << ' ' << v<< endl;
		int ru = find(u), rv = find(v);
		if(-R[ru] <= -R[rv])
		{
			R[rv] += R[ru];
			R[ru] = rv;
		}
		else if(-R[ru] > -R[rv])
		{
			R[ru] += R[rv];
			R[rv] = ru;
		}
	}

int N, M;
pair<int, int> V[MAX]; // (v[i], id)
vector<int> G[MAX];

ll calc(vector<int>& v)
{
	ll sum = 0, sum2 = 0;
	for(int i = 0; i < v.size(); i++) sum += v[i], sum2 += ((ll)v[i]) * v[i];
	return (sum * sum - sum2) / 2 + sum;
}

void print(vector<int>& V)
{
	cout << "<";
	for(int i = 0; i < V.size(); i++) cout << V[i] << ' ';
	cout << ">\n";
}

bool used[MAX];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
	{
		cin >> V[i].first;
		V[i].second = i;
	}
	for(int i = 0; i < M; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	sort(V + 1, V + 1 + N, greater< pair<int, int> >());

	memset(used, 0, sizeof(used));
	init();
	ll total = 0;
	for(int i = 1; i <= N; i++)
	{
		int u = V[i].second;
		set<int> reps;
		for(int j = 0; j < G[u].size(); j++)
		{
			int v = G[u][j];
			if(!used[v]) continue;
			int rv = find(v);
			reps.insert(rv);
			//cout << u << " -> " << v << ", rep = " << rv << ", size = " << -R[rv] << endl;
		}
		vector<int> sizes;
		for(set<int>::iterator it = reps.begin(); it != reps.end(); it++)
		{
			//cout << *it << ' ';
			sizes.push_back(-R[*it]);
		}
		ll add = V[i].first * calc(sizes);
		//cout << u << ": " << add << endl;
		total += add;
		for(int j = 0; j < G[u].size(); j++)
		{
			int v = G[u][j];
			if(!used[v]) continue;
			int ru = find(u), rv = find(v);
			if(ru != rv) uni(u, v);
		}
		used[u] = true;
	}
	double num = total, denom = ((ll)(N)) * (N - 1) / 2;
	printf("%.9f\n", num / denom);
}
