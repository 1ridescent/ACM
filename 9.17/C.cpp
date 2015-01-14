#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int inf = 255;

int N;
int A[20];
int dp[1 << 20];

vector<int> V;

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> A[i];
	for(int i = 0; i < (1 << N); i++) dp[i] = inf;
	dp[0] = 0;
	for(int b = 0; b < (1 << N) - 1; b++)
	{
		for(int i = 0; i < N; i++)
		{
			if(!(b & (1 << i))) V.push_back(i);
		}
		for(int ii = 0; ii < V.size(); ii++)
		{
			int i = V[ii];
			int b2 = (b | (1 << i));
			dp[b2] = min(dp[b2], dp[b] + A[i]);
			for(int ji = ii + 1; ji < V.size(); ji++)
			{
				int j = V[ji];
				b2 = (b | ((1 << i) | (1 << j)));
				dp[b2] = min(dp[b2], dp[b] + max(A[i], A[j]) + 1);
			}
		}
		V.clear();
	}
	cout << dp[(1 << N) - 1] << endl;
}
