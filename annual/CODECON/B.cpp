#include <iostream>

using namespace std;

bool good[9999];

int main()
{
	int D;
	cin >> D;
	int N;
	cin >> N;
	for(int i = 0; i < 96; i++) good[i] = true;
	for(int t = 0; t < N; t++)
	{
		string S;
		cin >> S;
		int B;
		cin >> B;
		for(int i = 0; i < B; i++)
		{
			int s, t;
			cin >> s >> t;
			for(int j = s; j < t; j++) good[j] = false;
		}
	}
	for(int i = 0; i < 96; i++)
	{
		bool res = true;
		for(int d = 0; d < D; d++)
			if(!good[i + d]) res = false;
		if(res)
		{
			cout << i << '\n';
			return 0;
		}
	}
	cout << "-1\n";
}
