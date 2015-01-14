#include <iostream>
#include <cstdio>

using namespace std;

double power(double b, int e)
{
	if(e == 0) return 1.0;
	double res = power(b, e / 2);
	res = res * res;
	if(e % 2) res *= b;
	return res;
}

int main()
{
	int M, N;
	cin >> M >> N;
	double res = 0;
	for(int t = 1; t <= M; t++)
	{
		double prob = power(t * 1.0 / M, N) - power((t - 1) * 1.0 / M, N);
		res += prob * t;
	}
	printf("%.9f\n", res);
}
