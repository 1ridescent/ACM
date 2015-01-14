#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

double L, K, T1, T2, H;
int main()
{
	cin >> L >> K >> T1 >> T2 >> H;
	if(H < L)
	{
		printf("%.9f %.9f\n", H, H);
		return 0;
	}
	double O = T2 * K + H - L;
	double A = T1;
	double B = -K * T1 - L - O;
	double C = L * K;
	//cout << O << ' ' << A << ' ' << B << ' ' << C << endl;
	if(B * B - 4 * A * C < 0) return 1;
	double r = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
	//cout << r << endl; return 0;
	double high = r * T1;
	if(H == L)
	{
		printf("%.9f %.9f\n", H, high);
	}
	else printf("%.9f %.9f\n", high, high);
}
