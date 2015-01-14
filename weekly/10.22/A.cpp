#include <iostream>

using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int N, D;
		cin >> N >> D;
		int cnt = 0;
		for(int i = 0; i < N; i++)
		{
			int V, F, C;
			cin >> V >> F >> C;
			if(D * C <= F * V) cnt++;
		}
		cout << cnt << '\n';
	}
}
