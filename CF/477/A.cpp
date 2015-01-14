#include <iostream>

using namespace std;

#define MOD(x) ((x) % 1000000007)

int main()
{
	long long a, b;
	cin >> a >> b;
	long long a1 = MOD(a * (a + 1) / 2);
	long long b1 = MOD(b * (b - 1) / 2);
	cout << MOD(a1 * MOD(b1 * b) + a * b1);
}
