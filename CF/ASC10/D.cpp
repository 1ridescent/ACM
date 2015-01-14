#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

ll N;

ll primes[14] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43 };
//ll powers[14] = { 6, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  ll powers[14] = { 10,7, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2 };

ll bestnum, besttotal = 0;
void compute(int index, ll num, int total)
{
	if(index == 14)
	{
		if(total > besttotal || (total == besttotal && num < bestnum))
		{
			bestnum = num;
			besttotal = total;
		}
		return;
	}
	ll nextnum = num;
	for(int p = 0; p < powers[index] + 1; p++)
	{
		compute(index + 1, nextnum, total * (p + 1));
		nextnum *= primes[index];
		if(nextnum > N) break;
	}
}

int main()
{
	//freopen("divisors.in", "r", stdin); freopen("divisors.out", "w", stdout);
	cin >> N;
	compute(0, 1, 1);
	cout << bestnum << endl;
	return 0;
}
