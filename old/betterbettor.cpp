#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

// "all bets cost one dollar and pay out two dollars" 0:24 into programming this, I had thought that either you gain 2 dollars or lose 1 dollar... lol...
// time before first submit = 0:28

const int MAX = 21000;

double refund, win;
double prob[2*MAX+10]; // [i][j]: prob of hitting i before -1

int main()
{
	cin >> refund >> win;
	refund /= 100;
	win /= 100;
	prob[1] = win;
	for(int k = 2; k <= 2*MAX; k++) prob[k] = win * prob[k-1] * 1.0/(1 - (1 - prob[k-1]) * win);
	double best = 0;
	for(int high = 1; high <= MAX/8; high++)
	{
		if(high > MAX/100 && high % 4 != 0) continue;
		double pass = 0;
		double fail = 1;
		for(int low = 1; low <= MAX; low++)
		{
			pass += fail * prob[high + low - 1];
			best = max(best, pass * high + (1-pass)*(1-refund) * -low);
			fail *= (1 - prob[high + low - 1]);
		}
	}
	printf("%.12f\n", best);
	return 0;
}
