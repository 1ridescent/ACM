#include <bits/stdc++.h>

using namespace std;

int N;
int M[100005];

double A[100005];
double L[100005], R[100005];
bool test(double r)
{
	for(int i = 1; i <= N; i++)
		A[i] = M[i] - r;
	L[2] = A[1];
	for(int i = 3; i <= N; i++)
		L[i] = L[i - 1] + A[i - 1];
	for(int i = 3; i <= N; i++)
		L[i] = min(L[i], L[i - 1]);
	R[N - 1] = A[N];
	for(int i = N - 2; i >= 1; i--)
		R[i] = R[i + 1] + A[i + 1];
	for(int i = N - 2; i >= 1; i--)
		R[i] = min(R[i], R[i + 1]);
	for(int i = 2; i < N; i++)
		if(L[i] + R[i] <= 0)
		{
			//cout << i << ' ' << L[i] << ' ' << R[i] << endl;
			return true;
		}
	return false;
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
		cin >> M[i];
	double low = 0, high = 12345;
	while(low + 1e-8 < high)
	{
		double mid = (low + high) / 2;
		//cout << mid << ' ' << test(mid) << endl;
		if(test(mid)) high = mid;
		else low = mid;
	}
	printf("%.3f\n", high);
}
