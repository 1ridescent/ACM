#include <bits/stdc++.h>

using namespace std;

int N, M;
string input[22];
int input2[22][22];

int next_id;
char B[22][22];
int cost[22][22];
int cheapest[22];

int dp[1 << 20];

int main()
{
	cin >> N >> M;

	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			cin >> B[i][j];
	for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				cin >> cost[i][j];

	for(int i = 0; i < N; i++)
	{
		cheapest[i] = (1 << 30);
		for(int j = 0; j < M; j++)
			cheapest[i] = min(cheapest[i], cost[i][j]);
	}

	for(int i = 0; i < (1 << N); i++)
		dp[i] = (1 << 30);
	dp[0] = 0;
	for(int j = 0; j < M; j++)
	{
		for(char c = 'a'; c <= 'z'; c++)
		{
			int total = 0, largest = 0;
			int mask = 0;
			for(int i = 0; i < N; i++)
				if(B[i][j] == c)
				{
					total += cost[i][j];
					largest = max(largest, cost[i][j]);
					mask |= (1 << i);
				}
			if(mask)
			{
				int add = total - largest;
				//printf("j=%d char=%c mask=%d add=%d\n", j, c, mask, add);
				for(int b = 0; b < (1 << N); b++)
					if(dp[b | mask] > dp[b] + add)
						dp[b | mask] = dp[b] + add;
			}
		}
	}

	int best = (1 << 30);
	for(int b = 0; b < (1 << N); b++)
	{
		int add = 0;
		for(int i = 0; i < N; i++)
			if(!(b & (1 << i)))
				add += cheapest[i];
		//printf("b=%d add=%d\n", b, add);
		best = min(best, dp[b] + add);
	}
	cout << best << endl;
}
