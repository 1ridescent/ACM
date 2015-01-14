#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

bool isprime[1000100];
void sieve()
{
	memset(isprime, 255, sizeof(isprime));
	for(int i = 2; i <= 1000000; i++)
	{
		if(isprime[i])
		{
			for(int j = i + i; j <= 1000000; j += i)
				isprime[j] = false;
		}
	}
}
int numdig(int x)
{
	int r = 0;
	for(; x; x /= 10) r++;
	return r;
}
int pow10(int x)
{
	int r = 1;
	while(x--) r *= 10;
	return r;
}

int dp[1010][1010];

int main()
{
	sieve();
	int N;
	cin >> N;
	memset(dp, 0, sizeof(dp));
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
		{
			if(i + j == 2) continue;
			if(i > 1) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
			if(j > 1) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
			if(isprime[i * pow10(numdig(j)) + j]) dp[i][j]++;
		}
	cout << dp[N][N]<<endl;
}
