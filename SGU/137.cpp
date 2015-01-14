#include <iostream>

using namespace std;

struct Euclid
{
	int x, y, q;
	void euclid(int a, int b)
	{
		if(b == 0) x = 1, y = 0, q = a;
		else
		{
			euclid(b, a % b);
			int temp = x;
			x = y;
			y = temp - a / b * y;
		}
	}
};
int mod_inverse(int a, int m)
{
	Euclid E;
	E.euclid(a, m);
	return (E.x + m) % m;
}

int res[1010];
int main()
{
	int N, K;
	cin >> N >> K;
	int q = K / N, r = K % N;
	for(int i = 0; i < N; i++) res[i] = q;
	int r1 = mod_inverse(r, N);
	for(int i = 0; i < r; i++) res[(r1 * i) % N]++;
	for(int i = 0; i < N; i++) cout << res[(i + 1) % N] << ' ';
}
