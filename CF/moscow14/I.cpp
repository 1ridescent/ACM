#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <set>

using namespace std;

typedef long double ld;

int N;
vector<int> primes;
bool isprime[300005];
void sieve()
{
	memset(isprime, -1, sizeof(isprime));
	for(int i = 2; i <= N; i++)
		if(isprime[i])
		{
			primes.push_back(i);
			for(int j = i + i; j <= N; j += i)
				isprime[j] = false;
		}
}

char interact(int x)
{
	cout << x << '\n';
	cout.flush();
	string s;
	if(!(cin >> s)) exit(0);
	if(s == "OK") exit(0);
	return s[0];
}

int round(ld x)
{
	return (int)(x + 0.5);
}

int main()
{
	cin >> N;
	sieve();

	string S;
	for(int i = 0; i < 41; i++) S += interact(2);

	ld frac = 0, scale = 1;
	for(int i = 0; i < 41; i++)
	{
		scale /= 2;
		if(S[i] == '<') frac += scale;
	}

	ld best = 1.0, best_p = -1;
	for(int i = 0; i < primes.size(); i++)
	{
		int p = primes[i];
		int rem = round(frac * p);
		ld diff = (frac - (ld)rem / p);
		if(diff < 0) diff = -diff;
		if(diff < best)
		{
			best = diff;
			best_p = p;
		}
	}
	interact(best_p);
	return -1;
}
