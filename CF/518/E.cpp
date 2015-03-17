#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;
ll A[500000];

ll pref[500000];
void setup()
{
	for(int i = 1; i <= N; i++)
		pref[i + 222222] = pref[i + 222221] + A[i];
}
ll seg(int l, int r)
{
	l += 222222;
	r += 222222;
	return pref[r] - pref[l - 1];
}

ll to_int(string S)
{
	int sign = 1;
	if(S[0] == '-')
	{
		sign = -1;
		S = S.substr(1);
	}
	ll val = 0;
	for(int i = 0; i < S.size(); i++)
	{
		val *= 10;
		val += (S[i] - '0');
	}
	return sign * val;
}

bool Q[100005];

vector<ll> V;
ll L[100005], R[100005];
int find_pivot()
{

}

int main()
{
	cin >> N >> K;
	for(int i = 1; i <= N; i++)
	{
		string s;
		cin >> s;
		if(s[0] == '?') Q[i] = true;
		else A[i] = to_int(s);
	}
	setup();
	for(int s = 1; s <= K - 1; s += K - 1)
	{
		int t =
	}
}
