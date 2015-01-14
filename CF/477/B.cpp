#include <iostream>

using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;
	cout << (6 * N - 1) * K << '\n';
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= 5; j++)
		{
			if(j == 4) continue;
			cout << (6 * (i - 1) + j) * K << ' ';
		}
		cout << '\n';
	}
}
