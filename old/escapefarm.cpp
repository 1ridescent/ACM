#include <iostream>

using namespace std;

int C[22][10];

int main()
{
	int N;
	cin >> N;
	for(int i = 0; i < 22; i++) for(int j = 0; j < 10; j++) C[i][j] = 0;
	for(int i = 0; i < N; i++)
	{
		string s;
		cin >> s;
		for(int j = 0; j < s.size(); j++) C[i][j] += (s[s.size()-1-j] - '0');
	}
	int best = 0;
	for(int b = 0; b < (1<<N); b++)
	{
		int check[10];
		for(int i = 0; i < 10; i++) check[i] = 0;
		int numbits = 0;
		for(int i = 0; i < N; i++)
		{
			if((1<<i) & b)
			{
				numbits++;
				for(int j = 0; j < N; j++) check[j] += C[i][j];
			}
		}
		bool good = true;
		for(int i = 0; i < 10; i++) if(check[i] >= 10) good = false;
		if(good && numbits > best)
		{
			best = numbits;
		}
	}
	cout << best << endl;
	return 0;
}
