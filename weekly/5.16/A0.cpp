#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 1e17;

const int MAX = 212;

#define SRC 1
#define TEMP 2
#define SNK 210
#define NODE(v) (4 + (v))

ll C[MAX][MAX], cap[MAX][MAX], flow[MAX][MAX], dist[MAX], pi[MAX], cost[MAX][MAX], dad[MAX], typ[MAX];
int match[MAX];
bool done[MAX];

ll total_cost = 0;

bool path()
{
	memset(done, 0, sizeof(done));
	for(int i = 0; i <= SNK; i++) dist[i] = INF;
	dist[SRC] = 0;
	while(true)
	{
		int x = -1;
		for(int i = 0; i <= SNK; i++)
			if(!done[i] && (x == -1 || dist[i] < dist[x]))
				x = i;
		if(x == -1) break;
		done[x] = true;
		for(int i = 0; i <= SNK; i++) {
			if (done[i]) continue;
			if(flow[x][i] < cap[x][i])
			{
				printf("found %d %d flow %lld %lld\n", x, i, flow[x][i], cap[x][i]); fflush(stdout);
				ll nd = dist[x] + cost[x][i];
				if(nd < dist[i])
				{
					dist[i] = nd;
					dad[i] = x;
					typ[i] = 0;
				}
			}
			if(flow[i][x])
			{
				printf("found rev %d %d flow\n", x, i);fflush(stdout);
				ll nd = dist[x] - cost[i][x];
				if(nd < dist[i])
				{
					dist[i] = nd;
					dad[i] = x;
					typ[i] = 1;
				}
			}
		}
	}
	if(dist[SNK] == INF) return false;
	int x = SNK;
	ll f = INF;
	while(x != SRC)
	{
		if (typ[x]) f = min(f, flow[x][dad[x]]);
		else f = min(f, cap[dad[x]][x] - flow[dad[x]][x]);
		x = dad[x];
	}
	x = SNK;
	while(x != SRC)
	{
		if (typ[x]) {
			flow[x][dad[x]] -= f;
			total_cost += f * -C[x][dad[x]];
		}
		else {
			flow[dad[x]][x] += f;
			total_cost += f * C[dad[x]][x];
		}
		x = dad[x];
	}
	for(int i = 0; i <= SNK; i++)
		pi[i] = min(pi[i] + dist[i], INF);
	cout << "found flow size " << f << endl;
	cout << "total cost is " << total_cost << endl;
	return true;
}
void minCostFlow()
{
	memset(pi, 0, sizeof(pi));
	while(true)
	{
		for(int i = 0; i <= SNK; i++)
			for(int j = 0; j <= SNK; j++)
				cost[i][j] = C[i][j] + pi[i] - pi[j];
		if(!path()) break;
	}
}
void add_edge(int u, int v, ll cp, ll cst)
{
	C[u][v] = cst;
	cap[u][v] = cp;
}

int N, M;
int H[MAX];
int trans[256][MAX];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> H[i];
	for(int i = 0; i <= N; i++)
	{
		add_edge(SRC, NODE(i), 2000100, 0);
		add_edge(NODE(i), SNK, 2000100, 0);
	}
	ll WEIGHT = 1e14;
	for(int i = 1; i < N; i++)
		add_edge(NODE(i), TEMP, 2000100 - (H[i + 1] - H[i]), -WEIGHT);
	add_edge(TEMP, SNK, 1e10, 0);
	while(M--)
	{
		char t;
		int l, c;
		cin >> t >> l >> c;
		if(trans[t][l]) trans[t][l] = min(trans[t][l], c);
		else trans[t][l] = c;
	}
	for(int l = 1; l <= N; l++)
	{
		if(trans['+'][l])
			for(int i = 1; i <= N; i++)
				add_edge(NODE(i), NODE(i - l), 2000100, trans['+'][l]);
		if(trans['-'][l])
			for(int i = 1; i <= N; i++)
				add_edge(NODE(i - l), NODE(i), 2000100, trans['-'][l]);
	}
	cout << "start flow" << endl;
	minCostFlow();
	cout << "end flow" << endl;
	for(int i = 1; i < N; i++)
	{
		if(flow[NODE(i)][TEMP] != cap[NODE(i)][TEMP])
		{
			cout << "-1\n";
			return 0;
		}
	}
	ll ans = 0;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			if(cap[NODE(i)][NODE(j)]) {
				ans += flow[NODE(i)][NODE(j)] * C[NODE(i)][NODE(j)];
				cout << flow[NODE(i)][NODE(j)] << " " << C[NODE(i)][NODE(j)] << endl;
			}
	cout << ans << endl;
	//cout << total_cost << endl;
	//cout << total_cost + (N - 1) * WEIGHT << endl;
}
