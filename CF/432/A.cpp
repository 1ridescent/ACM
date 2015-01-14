#include <iostream>

using namespace std;

int main()
{
	int N, K;
	cin >> N >> K;
	int cnt = 0;
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		if(5 - x >= K) cnt++;
	}
	cout << cnt / 3 << endl;
}
