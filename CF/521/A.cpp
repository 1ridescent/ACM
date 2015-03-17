#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll mod = 1000000007;

ll power(ll b, int e)
{
	if(e == 0) return 1;
	return (b * power(b, e - 1)) % mod;
}

char t[4] = { 'A', 'T', 'C', 'G' };
int cnt[256];

int main()
{
	int n;cin>>n;
	string S;
	cin >> S;
	int m = 0;
	for(int i = 0;i  < S.size(); i++) cnt[S[i]]++;
	for(int i = 0; i < 4; i++)
	{
		char c = t[i];
		m  = max(m, cnt[c]);
	}
	int s = 0;
	for(int i = 0; i < 4; i++)
	{
		char c=  t[i];
		s += (m == cnt[c]);
	}
	cout << power(s, S.size());
}
