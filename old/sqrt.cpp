#include <iostream>

using namespace std;

int main()
{
	double x;
	cin >> x;
	double i = false;
	if(x < 0)
	{
		x *= -1;
		i = true;
	}
	double low = 0, high = x+1;
	while(low + 1e-9 < high)
	{
		double mid = (low+high)/2;
		if(mid * mid <= x) low = mid;
		else high = mid;
	}
	cout << low;
	return 0;
}
