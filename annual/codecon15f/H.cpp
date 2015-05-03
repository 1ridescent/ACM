#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

int R, C;
int S[305][305];

int num_sol = 0;
int sol[305][305];

void Try()
{

}

int dp[305][3005];

int main()
{
	cin >> R >> C;
	for(int i = 1; i <= R; i++)
		for(int j = 1; j <= C; j++)
			cin >> S[i][j];
	if(R == 1 && C == 1)
	{
		int x = S[1][1];
		int num = 0, val;
		for(int i = x - 1; i <= x + 1; i += 2)
			if(0 <= i && i <= 9)
			{
				val = i;
				num++;
			}
		if(num == 1) cout << val << endl;
		else cout << num << " SOLUTIONS\n";
		return 0;
	}
	else if(R == 1)
	{
		dp[0][0] = 1;
		for(int i = 1; i <= C; i++)
		map<int, int> freq;
		for(int c = 1; c <= C; c++)
			freq[S[1][c]]++;
		for(map<int, int>::iterator it = freq.begin(); it != freq.end(); it++)
		{
			if(it->second == C - 1)
			{
				if(freq[it->first - 1] || freq[it->first + 1])
				{
					int sum = it->first;
					if(sum == 0 || sum == 9 * C)
					{
						for(int i = 0; i < C; i++)
						{
							if(i) cout << ' ';
							 cout << sum / C;
						}
						cout << endl;
					}
					for(int i = 1; i <= C; i++)
						for(int s = 0; s <= 2977; s++)
							for(int k = 0; k <= 9; k++)
								dp[i][s + k] = (dp[i][s + k] + dp[i - 1][s]) % 10007;
					cout << dp[C][sum] << " SOLUTIONS\n";
					return 0;
				}
			}
			cout << "0 SOLUTIONS\n";
			return 0;
		}
	}
	return 0;
}
