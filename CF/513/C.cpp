#include <bits/stdc++.h>

using namespace std;

int N;
int L[11], R[11];

int main()
{
	cin >> N;
	long double denom = 1;
	for(int i = 0; i < N; i++)
	{
		cin >> L[i] >> R[i];
		denom *= (R[i] - L[i] + 1);
	}
	long double total = 0;
	for(int w = 0; w < N; w++)
	{
		for(int b = 1; b < (1 << N); b++) // second places
		{
			if(b & (1 << w)) continue;
			for(int p = 1; p <= 10000; p++) // second price
			{
				bool poss = true;
				for(int i = 0; i < N; i++)
					if(b & (1 << i))
						if(!(L[i] <= p && p <= R[i]))
							poss = false;
				if(!poss) continue;
				double num = 1;
				for(int i = 0; i < N; i++)
				{
					if(i == w) num *= max(0, R[i] - max(p, L[i] - 1));
					else if(!(b & (1 << i))) num *= max(0, min(p, R[i] + 1) - L[i]);
				}
				total += p * num;
			}
		}
	}
	for(int b = 0; b < (1 << N); b++) // calc tie
	{
		if(__builtin_popcount(b) < 2) continue;
		for(int p = 1; p <= 10000; p++)
		{
			bool poss = true;
			for(int i = 0; i < N; i++)
				if(b & (1 << i))
					if(!(L[i] <= p && p <= R[i]))
						poss = false;
			if(!poss) continue;
			double num = 1;
			for(int i = 0; i < N; i++)
				if(!(b & (1 << i)))
				{
					//cout << max(0, min(p, R[i] + 1) - L[i]) << ' ';
					num *= max(0, min(p, R[i] + 1) - L[i]);
				}
			total += p * num;
			//cout << b << ' ' << p << ' ' << num << endl;
		}
	}
	printf("%.12f\n", (double)(total/denom));//cout << total << ' ' << denom;
}
