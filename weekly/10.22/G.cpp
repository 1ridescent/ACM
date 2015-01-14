#include <iostream>

using namespace std;

typedef long long ll;
ll A[68];

void pre()
{
	A[0] = A[1] = 1;
	A[2] = 2;
	A[3] = 4;
	for(int i = 4; i <= 67; i++) A[i] = A[i-1]+A[i-2]+A[i-3]+A[i-4];
}

int main()
{
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	pre();
	while(N--)
	{
		int x;
		cin >> x;
		cout << A[x] << '\n';
	}
}
