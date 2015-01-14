#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> primes;

void get_primes()
{
	for(int p = 2; p <= N; p++)
	{
		int good = true;
		for(int d = 2; d * d <= p; d++)
		{
			if(p % d == 0) good = false;
		}
		if(good) primes.push_back(p);
	}
}

int main()
{
	cin >> N;
	get_primes();
	for(int i = 0 ; i < primes.size(); i++) cout << primes[i]<< ' ';
}
