#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int log2(ll x)
{
	for(int i = 63; i >= 0; i--)
		if(x & (1LL << i))
			return i;
}
int num_complete(ll x)
{
	if(x == 1) return 1;
	int i = log2(x);
	if(x < (1LL << i) + (1LL << (i - 1)) - 1) return i - 1;
	else if(x < (1LL << (i + 1)) - 1) return i;
	return i + 1;
}
int num_incomplete(ll x)
{
	for(int i = 0; i <= 63; i++)
	{
		if(!(x & (1LL << i)))
		{
			if((1LL << i) > x) return 0;
			return (log2(x) - i);
		}
	}
}

int main()
{
	//while(true){ll x;cin>>x;cout<<num_complete(x)<<endl;}
	//for(int i=1;i<=20;i++)cout<<num_incomplete(i);
	int T;
	cin >> T;
	while(T--)
	{
		ll x;
		cin >> x;
		if(x == 1) cout << 1 << '\n';
		else cout << log2(x) + num_complete(x) - 1 + num_incomplete(x) << '\n';
	}
}
