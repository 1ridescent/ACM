#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int N;
ll A[1000005];

vector<ll> V;
vector< pair<int, char> > P; // (index, h/l)
ll dp[1000005][2]; // [index][last used?]
ll solve()
{
	if(V.size() <= 1)
	{
		V.clear();
		return 0;
	}

	//cout << V.size() << endl;

	P.push_back(make_pair(0, (V[0] > V[1] ? 'h' : 'l')));
	for(int i = 1; i < V.size() - 1; i++)
	{
		if(V[i] > V[i - 1] && V[i] > V[i + 1]) P.push_back(make_pair(i, 'h'));
		else if(V[i] < V[i - 1] && V[i] < V[i + 1]) P.push_back(make_pair(i, 'l'));
	}
	P.push_back(make_pair(V.size() - 1, (V[V.size() - 1] > V[V.size() - 2] ? 'h' : 'l')));

	dp[0][0] = dp[1][0] = 0;
	for(int i = 1; i < P.size(); i++)
	{
		int s = P[i - 1].first, t = P[i].first;

		// don't use i
		dp[i][0] = max(dp[i - 1][0] + abs(V[s] - V[t - 1]),
			           dp[i - 1][1] + ((s + 1 == t) ? 0 : (abs(V[s + 1] - V[t - 1]))));

		// use i
		dp[i][1] = max(dp[i - 1][0] + abs(V[s] - V[t]),
				       dp[i - 1][1] + abs(V[s + 1] - V[t]));

		//cout << dp[i][0] << ' ' << dp[i][1] << endl;
	}

	int p = P.size() - 1;

	V.clear();
	P.clear();

	return max(dp[p][0], dp[p][1]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;

	ll ans = 0;
	for(int i = 0; i < N; i++)
	{
		cin >> A[i];
		if(i > 0 && A[i] == A[i - 1]) ans += solve();
		V.push_back(A[i]);
	}
	cout << ans + solve();
}
