#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
int A[100005];

int main()
{
	int T;
	cin >> T;
	for(int test = 1; test <= T; test++)
	{
		cin >> N;
		for(int i = 1; i <= N; i++) cin >> A[i];
		ll res = 0;
		for(int i = 1; i <= N; i++)
			res += max(A[i] - A[i - 1], 0);
		cout << "Case #" << test << ": " << res << ' ';
		res = 0;
		for(ll r = 1; r <= 1005; r++)
		{
			for(int i = 1; i <= N; i++
		}
	}
}
