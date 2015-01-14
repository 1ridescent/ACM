#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int N, M;
int S[1000100];
bool poss[2000200];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
	{
		char c;
		cin >> c;
		//cout << c << ' ';
		if(c == 'W') S[i] = 1;
		else S[i] = 2;
	}
	memset(poss, 0, sizeof(poss));

	int num1 = 0;
	for(int i = 1; i <= N; i++)
		num1 += (S[i] == 1);

	//cout << "num1 = " << num1 << endl;
	if(num1 == 0) // all 2's
	{
		for(int i = 1; i <= N; i++) poss[i * 2] = true;
	}
	else
	{
		int first, last;
		for(int i = 1; i <= N; i++)
		{
			if(S[i] == 1)
			{
				first = i;
				break;
			}
		}
		for(int i = N; i >= 1; i--)
		{
			if(S[i] == 1)
			{
				last = i;
				break;
			}
		}

		int firstsum = 0;
		for(int i = 1; i <= last; i++) firstsum += S[i];
		for(int i = 1; i <= firstsum; i++) poss[i] = true;

		int lastsum = 0;
		for(int i = N; i >= first; i--) lastsum += S[i];
		for(int i = 1; i <= lastsum; i++) poss[i] = true;

		int midsum = 0;
		for(int i = first; i <= last; i++) midsum += S[i];
		for(int i = last + 1; i <= N; i++)
		{
			midsum += S[i];
			poss[midsum] = true;
		}
		for(int i = 1; i < first; i++)
		{
			midsum += S[i];
			poss[midsum] = true;
		}
	}

	//for(int i = 1; i <= 2 * N; i++) cout << poss[i]; cout << endl;
	while(M--)
	{
		int x;
		cin >> x;
		cout << (poss[x] ? "TAK\n" : "NIE\n");
	}
}
