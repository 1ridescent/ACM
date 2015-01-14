#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

double prev[5050];
double delta[5050];
double next[5050];

double power[5050]; // (1 - p)
void incr(double p, int t)
{
	power[0] = 1;
	for(int i = 1; i <= 5005; i++)
		power[i] = (1 - p) * power[i - 1];

	memset(delta, 0, sizeof(delta));
	for(int i = 0; i <= 5005; i++)
	{
		delta[i + 1] += p * prev[i];
		if(i + t <= 5005)
		{
			delta[i + t] += power[t] * prev[i];
			delta[i + t + 1] -= power[t] * prev[i];
		}
	}
	next[0] = delta[0];
	for(int i = 1; i <= 5005; i++)
		next[i] = (1 - p) * next[i - 1] + delta[i];
}

int N, T;

int main()
{
	cin >> N >> T;
	long double ans = 0;
	memset(prev, 0, sizeof(prev));
	prev[0] = 1;
	for(int n = 1; n <= N; n++)
	{
		double p;
		int t;
		cin >> p >> t;
		p /= 100.0;
		incr(p, t);
		for(int i = 0; i <= T; i++)
			ans += next[i];
		memcpy(prev, next, sizeof(next));
	}
	printf("%.9f\n", (double)ans);
}
