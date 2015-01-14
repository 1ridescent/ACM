#include <iostream>
#include <algorithm>

using namespace std;

int A[10010];
int total = 0;

int main()
{
	int N;
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		cin >> A[i];
		total += A[i];
	}
	int avg = total / N;
	int res = 0;
	for(int i = 0; i < N; i++) res += abs(avg - A[i]);
	cout << (res+1)/2 << endl;
	return 0;
}
