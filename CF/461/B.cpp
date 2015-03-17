#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

int N;
vector<int> T[101010];
int C[101010];
ll W[2][101010];

int main()
{
	cin >> N;
	T[0].push_back(1);
	for(int i = 2; i <= N; i++)
	{
		int u, v = i;
		cin >> u;
		u++;
		T[u].push_back(v);
	}
	for(int i = 1; i <= N; i++) cin >> C[i];
	for(int u = N; u >= 0; u--)
	{
		if(C[u])
		{
			ll w = 1;
			for(int i = 0; i < T[u].size(); i++)
			{
				int v = T[u][i];
				w = (w * (W[0][v] + W[1][v])) % mod;
			}
			W[1][u] = w;
			W[0][u] = 0;
		}
		else
		{
			ll w[2];
			w[0] = 1, w[1] = 0;
			for(int i = 0; i < T[u].size(); i++)
			{
				int v = T[u][i];
				w[1] = (w[1] * (W[0][v] + W[1][v])) % mod;
				w[1] = (w[1] + w[0] * W[1][v]) % mod;
				w[0] = (w[0] * (W[0][v] + W[1][v])) % mod;
			}
			W[1][u] = w[1];
			W[0][u] = w[0];
		}
		//cout << u << ' ' << W[0][u] << ' ' << W[1][u] << endl;
	}
	cout << W[1][0];
}
