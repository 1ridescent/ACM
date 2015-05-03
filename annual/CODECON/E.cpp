#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int N;
int K;
int S[7];

bool vis[105];
bool memo[105];
bool go(int n) // n coins left. can I win?
{
	if(n == 0) return false;
	if(vis[n]) return memo[n];
	for(int i = 0; i < K; i++)
	{
		int s = S[i];
		if(s > n) continue;
		if(!go(n - s))
		{
			memo[n] = true;
			return true;
		}
	}
	memo[n] = false;
	return false;
}

int main()
{
	cin >> N >> K;
	for(int i = 0; i < K; i++) cin >> S[i];
	int best = 100000;
	for(int i = 0; i < K; i++)
	{
		int s = S[i];
		if(s > N) continue;
		if(!go(N - s)) best = min(best, s);
	}
	cout << (best == 100000 ? -1 : best) << '\n';
}
