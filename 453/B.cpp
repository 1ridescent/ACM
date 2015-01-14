#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 1000000000;

vector<int> primes;
int factors[65];

void pre()
{
	for(int i = 2; i <= 60; i++)
	{
		bool isprime = true;
		for(int j = 2; j < i; j++) if(i % j == 0) isprime = false;
		if(isprime) primes.push_back(i);
	}
	for(int i = 1; i <= 60; i++)
	{
		factors[i] = 0;
		for(int j = 0; j < primes.size(); j++) if(i % primes[j] == 0) factors[i] |= (1 << j);
	}
}

int N;
int A[105];
int dp[105][1 << 17];
int prev[105][1 << 17];

int main()
{
	pre();
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i];

	for(int i = 0; i < 105; i++) for(int j = 0; j < (1 << 17); j++) dp[i][j] = INF;
	memset(dp[0], 0, sizeof(dp[0]));

	for(int s = 1; s <= N; s++)
	{
		for(int b = 0; b < (1 << 17); b++)
		{
			for(int f = 1; f <= 60; f++)
			{
				if(b & factors[f]) continue;
				int val = dp[s - 1][b] + abs(A[s] - f);
				if(val < dp[s][b | factors[f]])
				{
					dp[s][b | factors[f]] = val;
					prev[s][b | factors[f]] = f;
				}
			}//
		}
	}

	int best = INF, cur_b;
	for(int b = 0; b < (1 << 17); b++)
	{
		if(dp[N][b] < best)
		{
			best = dp[N][b];
			cur_b = b;
		}
	}
	//cout << best << endl;

	int res[105];
	for(int s = N; s >= 1; s--)
	{
		res[s] = prev[s][cur_b];
		cur_b ^= factors[prev[s][cur_b]];
	}
	for(int i = 1; i <= N; i++) cout << res[i] << ' ';
}
