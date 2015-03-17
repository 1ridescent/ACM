#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll A[333333];

int main()
{
	int N;
	cin >> N;
	if(N == 1)
	{
		int x;
		cin >> x;
		cout << x;
		return 0;
	}
	for(int i = 0; i < N; i++) cin >> A[i];
	sort(A, A + N);
	ll a = 0;
	for(int i = 0; i < N; i++) a += max(2, min(i + 2, N)) * A[i];
	cout << a;
}
