#include <bits/stdc++.h>

using namespace std;

const unsigned int mod = 1000000007;

int N;
char B[512][512];
vector<char> V[1024];
unsigned int dp[512][512];
unsigned int temp[512][512];

int main()
{
	freopen("palpath.in","r",stdin);freopen("palpath.out","w",stdout);
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			char c;
			cin >> c;
			//cout << i << ' ' <<j<< ' '<<c<<endl;
			V[i + j].push_back(c);
		}
	if(V[0][0] != V[2 * N - 2][0])
	{
		cout << 0 << endl;
		return 0;
	}
	//for(int i=0;i<=N-2;i++)cout<<V[i].size()<<' ';cout<<endl;
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for(int s = 1; s < N; s++)
	{
		for(int i1 = 0; i1 <= s; i1++)
			for(int i2 = 0; i2 <= s; i2++)
			{
				temp[i1][i2] = 0;
				//cout << s << ' ' << i1 << ' ' << V[s].size() << ' ' << i2 << ' ' << V[N-2-s].size() << endl;
				if(V[s][i1] != V[2 * N - 2 - s][i2]) continue;
				if(i1 > 0 && i2 > 0 && V[s - 1][i1 - 1] == V[2 * N - 2 - (s - 1)][i2 - 1]) temp[i1][i2] += dp[i1 - 1][i2 - 1];
				if(i1 > 0 && V[s - 1][i1 - 1] == V[2 * N - 2 - (s - 1)][i2]) temp[i1][i2] += dp[i1 - 1][i2];
				if(i2 > 0 && V[s - 1][i1] == V[2 * N - 2 - (s - 1)][i2 - 1]) temp[i1][i2] += dp[i1][i2 - 1];
				if(V[s - 1][i1] == V[2 * N - 2 - (s - 1)][i2]) temp[i1][i2] += dp[i1][i2];
			}
		for(int i1 = 0; i1 <= s; i1++)
			for(int i2 = 0; i2 <= s; i2++)
				dp[i1][i2] = temp[i1][i2] % mod;
	}
	int ans = 0;
	for(int i = 0; i <= N - 1; i++)
		ans = (ans + dp[i][i]) % mod;
	cout << ans << endl;
}
