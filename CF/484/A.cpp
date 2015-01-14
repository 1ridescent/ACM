#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
	int Q;
	cin >> Q;
	while(Q--)
	{
		ll L, R;
		cin >> L >> R;
		R++;
		for(int i = 61; i >= 0; i--)
		{
			if((L & (1LL << i)) != (R & (1LL << i)))
			{
				cout << (R & (~((1LL << i) - 1))) - 1 << '\n';
				break;
			}
		}
	}
}
