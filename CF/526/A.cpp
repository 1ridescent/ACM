#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	string S;
	cin >> S;
	for(int i = 0; i < N; i++)
		for(int j = i + 1; j < N; j++)
		{
			int d = j - i;
			bool good = true;
			for(int k = 0; k < 5; k++)
			{
				int l = i + k * d;
				if(l >= N) good = false;
				else if(S[l] == '.') good = false;
			}
			if(good)
			{
				cout << "yes";
				return 0;
			}
		}
	cout << "no";
}
