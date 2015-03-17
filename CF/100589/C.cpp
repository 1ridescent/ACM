#include <iostream>

using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int N;
		string S;
		int P;
		cin >> N >> S >> P;
		if(S[0] == 'o')
		{
			cout << 2 * P << endl;
		}
		else
		{
			cout << 2 * P - 1 << endl;
		}
	}
}
