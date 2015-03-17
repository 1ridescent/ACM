#include <bits/stdc++.h>

using namespace std;

int N;
int A[1111111];
int L[1111111], R[1111111];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 1; i <= N; i++)
		L[i] = 1 + (A[i] > A[i - 1] ? L[i - 1] : 0);
	for(int i = N; i >= 1; i--)
		R[i] = 1 + (A[i] < A[i + 1] ? R[i + 1] : 0);
	int res = 0;
	for(int i = 1; i <= N; i++)
	{
		int a = L[i - 1], b = R[i + 1];
		if(A[i - 1] + 1 < A[i + 1]) res = max(res, 1 + a + b);
		else res = max(res, 1 + max(a, b));
	}
	cout << res;
}
