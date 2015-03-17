#include <iostream>

using namespace std;

typedef long long ll;

int N;
ll A[3000005];

int main()
{
	cin >> N;
	int k;
	cin >> k;
	while(k--)
	{
		ll x, y, a, b;
		cin >> x >> y >> a >> b;
		for(int i = 1; i <= y; i++)
			A[(a * i + b) % N] += x;
	}
	for(int i = 0; i < 3 * N; i++)
	{
		if(A[i % N] > 1)
		{
			A[(i + 1) % N] += (A[i % N] - 1);
			A[i % N] = 1;
		}
	}
	for(int i = 0; i < N; i++)
	{
		if(!A[i])
		{
			cout << i << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}
