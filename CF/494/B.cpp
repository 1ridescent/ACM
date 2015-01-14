#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

int T[100005];
void build_table(string& W)
{
	int pos = 2, cnd = 0;
	T[0] = -1, T[1] = 0;
	while(pos < W.size())
	{
		if(W[pos - 1] == W[cnd])
			cnd++, T[pos] = cnd, pos++;
		else if(cnd > 0)
			cnd = T[cnd];
		else
			T[pos] = 0, pos++;
	}
}

bool full[100005];
void kmp_search(string& S, string& W)
{
	memset(full, 0, sizeof(full));
	int m = 0, i = 0;
	while(m + i < S.size())
	{
		if(i == W.size() - 1) full[m] = true;
		if(W[i] == S[m + i])
			i++;
		else
		{
			if(T[i] > -1)
				m += i - T[i], i = T[i];
			else
				i = 0, m++;
		}
	}
}

int N, M;
string S, W;

ll dp[100005];
ll pref[100005];

int main()
{
	cin >> S >> W;
	N = S.size();
	M = W.size();
	S += "###";
	W += '$';
	build_table(W);
	kmp_search(S, W);
	//for(int i = 0; i < S.size(); i++) cout << full[i];

	memset(dp, 0, sizeof(dp));
	dp[N] = 1;
	pref[N] = 1;
	int last = -1;
	for(int i = N - 1; i >= 0; i--)
	{
		dp[i] += dp[i + 1];
		if(full[i]) last = i + M;
		if(last != -1)
		{
			dp[i] += pref[last];
		}
		dp[i] %= mod;
		//cout << i << " : " << dp[i] << endl;
		pref[i] = (pref[i + 1] + dp[i]) % mod;
	}
	cout << (dp[0] - 1 + mod) % mod;
}
