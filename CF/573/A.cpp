#include <bits/stdc++.h>

using namespace std;

int N;
int A[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		int x;
		cin >> x;
		while(x % 2 == 0) x /= 2;
		while(x % 3 == 0) x /= 3;
		A[i] = x;
	}
	for(int i = 2; i <= N; i++)
		if(A[i] != A[i - 1])
		{
			cout << "No\n";
			return 0;
		}
	cout << "Yes\n";
}
