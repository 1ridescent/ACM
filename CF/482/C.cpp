#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ll;

int N, L;
string S[52];

ll common[22][52];

int singles[1 << 21];

ll cur[52];
void dfs(int b, int t)
{
	if(t == L)
	{
		//cout << b << ": ";
		for(int i = 0; i < N; i++)
		{
			//printf("cur[%d] = %d\n", i, (int)cur[i]);
			if(cur[i] == 0)
				singles[b]++;
		}
		return;
	}
	// don't use
	dfs(b, t + 1);
	// use
	ll save[52];
	memcpy(save, cur, sizeof(cur));
	for(int i = 0; i < N; i++)
		cur[i] &= common[t][i];
	dfs(b + (1 << t), t + 1);
	memcpy(cur, save, sizeof(save));
}

bool vis[1 << 21];
long double dp[1 << 21];

double calc(int b)
{
	if(vis[b]) return dp[b];

	//printf("singles[%d]: %d\n", b, singles[b]);

	vis[b] = true;
	if(singles[b] == N)
		dp[b] = 1.0;
	else
	{
		int num_left = 0;
		for(int i = 0; i < L; i++)
		{
			int b2 = (b | (1 << i));
			if(b2 != b)
			{
				num_left++;
				int num_good = singles[b2] - singles[b];
				int num_bad = N - singles[b2];
				dp[b] += 1.0 * num_good / (num_good + num_bad);
				dp[b] += 1.0 * num_bad / (num_good + num_bad) * (1.0 + calc(b2));
			}
		}
		dp[b] /= num_left;
	}
	return dp[b];
}

int main()
{
	memset(singles, 0, sizeof(singles));

	cin >> N;

	if(N == 1) // f***ing troll
	{
		cout << "0\n";
		return 0;
	}

	for(int i = 0; i < N; i++) cin >> S[i];
	L = S[0].size();

	memset(common, 0, sizeof(common));
	for(int i = 0; i < L; i++)
		for(int j = 0; j < N; j++)
			for(int k = 0; k < N; k++)
				if(S[j][i] == S[k][i])
					common[i][j] |= (1LL << k);

	for(int i = 0; i < N; i++) cur[i] = (((1LL << N) - 1) ^ (1LL << i));

	dfs(0, 0);

	memset(vis, 0, sizeof(vis));

	/*for(int b = (1 << L) - 1; b >= 0; b--)
	{
		//printf("singles[%d]: %d\n", b, singles[b]);
		if(singles[b] == N)
		{
			dp[b] = 1.0;
			continue;
		}
		int num_left = 0;
		for(int i = 0; i < L; i++)
		{
			int b2 = (b | (1 << i));
			if(b2 != b)
			{
				num_left++;
				int num_good = singles[b2] - singles[b];
				int num_bad = N - singles[b2];
				dp[b] += 1.0 * num_bad / (num_good + num_bad) * (1.0 + dp[b2]);
			}
		}
		dp[b] /= num_left;
	}*/

	printf("%.12f\n", calc(0));
}
