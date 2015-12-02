#include <bits/stdc++.h>

using namespace std;

int dp[22222222]; // max num checks

int E, Es, Ef;

int main()
{
	cin >> E >> Es >> Ef;
	dp[0] = 0;
	for(int e = 1; e <= E; e++)
	{
		int Ns = dp[max(0, e - Es)];
		int Nf = dp[max(0, e - Ef)];
		dp[e] = min(1000000000, Ns + Nf + 1);
	}
	//cout << dp[E] << endl;
	int N = dp[E];
	double ans = max(0.0, min(225.0 / (N + 1), 200.0 / N));
	if(ans < 1e-7)
	{
		cout << "0.000000\n";
		return 0;
	}
	printf("%.6f\n", max(0.0, min(225.0 / (N + 1), 200.0 / N)));
}
