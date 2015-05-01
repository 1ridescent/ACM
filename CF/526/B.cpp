#include <bits/stdc++.h>

using namespace std;

const int MAX = 123123;

int N;
int A[MAX], T[MAX];

int main()
{
	cin >> N;
	for(int i = 2; i < (1 << (N + 1)); i++)
		cin >> A[i];
	long long total = 0;
	for(int p = (1 << N) - 1; p >= 1; p--)
	{
		int l = A[p * 2] + T[p * 2], r = A[p * 2 + 1] + T[p * 2 + 1];
		total += abs(l - r);
		T[p] = max(l, r);
	}
	cout << total;
}
