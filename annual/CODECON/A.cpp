#include <iostream>

using namespace std;

bool is_prime(int x)
{
	for(int i = 2; i < x; i++)
		if(x % i == 0) return false;
	return true;
}

int main()
{
	int n;
	cin >> n;
	for(int i = n - 2; i >= 0; i--)
		if(is_prime(i) && is_prime(i + 2))
		{
			cout << i << ',' << i + 2 << '\n';
			return 0;
		}
}
