#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef long long ll;

const int MAXLEN = 111;
const int SIZE = 2 * MAXLEN + 2;
#define OUTSIDE(x) ((x) < 0 || (x) >= SIZE)

int N;
vector< pair<int, int> > G0[30005];
vector<int> G[30005];
int P[30005];
int E[30005];

int label[30005];
int data[30005][SIZE];
void init(int u)
{
	memset(data[u], 0, sizeof(data[u]));
	label[u] = 1;
	data[u][MAXLEN]++;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		init(v);
		if(data[v][SIZE - 1] != 0)
			exit(-1); // too deep...
		for(int s = 0; s < SIZE - 1; s++)
		{
			data[u][s + 1] += data[v][s];
		}
	}
}

void diff(int v0, int d)
{
	int v = v0;
	int accum = 0;
	int u = P[v];
	while(u != -1)
	{
		accum += label[v];
		for(int s = 0; s < SIZE; s++)
		{
			if(OUTSIDE(accum + s)) continue;
			data[u][accum + s] += d * data[v0][s];
		}
		v = u;
		u = P[u];
	}
}

void update(int v)
{
	diff(v, -1);
	label[v] = -1;
	diff(v, 1);
}

void output()
{
	for(int i = 1; i <= N; i++)
	{
		cout << i << " > ";
		for(int s = -MAXLEN; s <= MAXLEN; s++)
			cout << s << ':' << data[i][s + MAXLEN] << ' ';
		cout << endl;
	}
	cout << endl;
}

int result[SIZE];
void output_result()
{
	cout << "result > ";
	for(int s = -MAXLEN; s <= MAXLEN; s++)
		cout << s << ':' << result[s + MAXLEN] << ' ';
	cout << endl;
}
void supertree(int v0)
{
	int v = v0;
	memset(result, 0, sizeof(result));
	int accum = -label[v0];
	int u = P[v];
	while(u != -1)
	{
		accum += label[v];
		int temp[SIZE];
		memset(temp, 0, sizeof(temp));
		for(int s = 0; s < SIZE; s++)
		{
			if(OUTSIDE(s - label[v])) continue;
			temp[s] += data[u][s] - data[v][s - label[v]];
		}
		for(int s = 0; s < SIZE; s++)
		{
			if(OUTSIDE(s + accum)) continue;
			result[s + accum] += temp[s];
		}
		v = u;
		u = P[u];
	}
}

void build_tree(int u, int p)
{
	for(int i = 0; i < G0[u].size(); i++)
	{
		int v = G0[u][i].first;
		int e = G0[u][i].second;
		if(v == p) continue;
		G[u].push_back(v);
		//cout << u << ' ' << v << ' ' << e << endl;
		P[v] = u;
		E[v] = e;
		build_tree(v, u);
	}
}

int main()
{
	freopen("hidden.in", "r", stdin); freopen("hidden.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		G0[a].push_back(make_pair(b, c));
		G0[b].push_back(make_pair(a, c));
	}
	P[1] = E[1] = -1;
	build_tree(1, -1);

	vector< pair<int, int> > edges;
	for(int i = 2; i <= N; i++)
		edges.push_back(make_pair(E[i], i));
	sort(edges.begin(), edges.end());

	init(1);

	//diff(4,-1);output();diff(4,1);output();return 0;
	//supertree(4);output_result();return 0;

	ll cnt[2] = {0, 0};
	for(int s = 0; s < SIZE; s++)
		cnt[s % 2] += data[1][s];
	ll num2 = cnt[0] * cnt[1];

	ll total = 0;
	for(int ei = 0; ei < edges.size(); ei++)
	{
		int v = edges[ei].second;
		int w = edges[ei].first;
		int u = P[v];
		//cout << u << ' ' << v << ' ' << w << endl;

		//output();
		//cout << "supertree at " << v << endl;
		supertree(v);
		//output_result();
		ll num = 0;
		for(int s = -MAXLEN; s <= MAXLEN; s++)
			num += result[MAXLEN + s] * data[v][MAXLEN - s];
		//cout << num << endl;

		total += num * w;

		update(v);

		//output();
	}

	cout << setprecision(12) << total * 1.0 / num2 << endl;
}
