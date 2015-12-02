#include <bits/stdc++.h>

using namespace std;

#define SQ(x) ((x) * (x))
#define EPS 1e-9

int N;
double X[5005], Y[5005];
vector<int> G0[5005];

#define SQDIST(i, j) (SQ(X[i] - X[j]) + SQ(Y[i] - Y[j]))

int size[5005];
int vis[5005];
void flood(int u, int c)
{
	vis[u] = c;
	size[c]++;
	for(int v : G0[u]) if(!vis[v]) flood(v, c);
}

vector<int> G[5005];
bool A[5005][5005];
int ans = 0;
vector<int> stk;
void dfs()
{
	//cout << " size " << stk.size() << endl;
	int u = stk.back();
	int s = 1;
	for(int v : stk) s += size[vis[v]];
	if(s > ans) ans = s;
	for(int v : G[u])
	{
		bool good = true;
		for(int w : stk)
			if(!A[w][v])
			{
				good = false;
				break;
			}
		if(good && stk.size() == 2)
		{
			double a = sqrt(SQDIST(stk[0], stk[1]));
			double b = sqrt(SQDIST(stk[1], v));
			double c = sqrt(SQDIST(v, stk[0]));
			double r = a*b*c / sqrt((a+b+c)*(a+b-c)*(a-b+c)*(-a+b+c));
			//cout << a << ' ' << b << ' ' << c << ' ' << r << endl;
			if(r > 2 + EPS) good = false;
		}

		if(good)
		{
			stk.push_back(v);
			dfs();
			stk.pop_back();
		}
	}
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> X[i] >> Y[i];
	for(int i = 0; i < N; i++)
		for(int j = i + 1; j < N; j++)
			if(SQDIST(i, j) < 4.0 + EPS)
			{
				G0[i].push_back(j);
				G0[j].push_back(i);
			}
	int next_c = 1;
	for(int i = 0; i < N; i++)
		if(!vis[i])
		{
			flood(i, next_c);
			next_c++;
		}
	for(int i = 0; i < N; i++)
		for(int j = i + 1; j < N; j++)
			if(SQDIST(i, j) < 16.0 + EPS)
				if(vis[i] != vis[j])
				{
					G[i].push_back(j);
					G[j].push_back(i);
					A[i][j] = A[j][i] = true;
				}
	for(int i = 0; i < N; i++)
	{
		stk.push_back(i);
		dfs();
		stk.pop_back();
	}
	cout << ans << endl;
}
