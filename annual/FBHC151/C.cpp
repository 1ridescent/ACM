#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

ll dp[2005][2005];

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		int A, B;
		cin >> A >> B;
		B *= -1;
		//cout << A << ' ' <<  B<<'\n';continue;
		cout << "Case #" << t << ": ";
		memset(dp, 0, sizeof(dp));
		dp[1][0] = 1;
		for(int a = 0; a <= A; a++)
			for(int b = 0; b < a; b++)
			{
				if(a - 1 > b) dp[a][b] += dp[a - 1][b];
				if(b > 0) dp[a][b] += dp[a][b - 1];
				dp[a][b] %= mod;
				//cout << a << ' ' << b << ' ' << dp[a][b] << endl;
			}
		cout << dp[A][B] << ' ';
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for(int a = 0; a <= B; a++)
			for(int b = 0; b <= a; b++)
			{
				if(a - 1 >= b) dp[a][b] += dp[a - 1][b];
				if(b > 0) dp[a][b] += dp[a][b - 1];
				dp[a][b] %= mod;
			}
		cout << dp[B][B] << endl;
	}
}
