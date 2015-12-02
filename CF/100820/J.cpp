#include <bits/stdc++.h>

using namespace std;

double dp[10000005]; // how close starting from range 1.0 ?

int E, Es, Ef;

int main()
{
	cin >> E >> Es >> Ef;
	dp[0] = 1.0;
	for(int e = 1; e <= E; e++)
	{
		double Rs = dp[max(0, e - Es)];
		double Rf = dp[max(0, e - Ef)];
		dp[e] = 1.0 / (1.0 / Rs + 1.0 / Rf);
	}
	cout << 200 * dp[E] << endl;
}
