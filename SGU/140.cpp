#include <iostream>
#include <cassert>

using namespace std;

typedef long long ll;

struct Euclid
{
	ll x, y, q;
	void euclid(ll a, ll b)
	{
		if(b == 0) x = 1, y = 0, q = a;
		else
		{
			euclid(b, a % b);
			ll temp = x;
			x = y;
			y = temp - a / b * y;
		}
	}
};
Euclid E;
ll N, P, B;
ll A[105];
ll X[105];

int main()
{
	cin >> N >> P >> B;
	for(int i = 0; i < N; i++) cin >> A[i];
	ll gcd = A[0];
	X[0] = 1;
	for(int i = 1; i < N; i++)
	{
		E.euclid(gcd, A[i]);
		gcd = E.q;
		for(int j = 0; j < i; j++)
		{
			X[j] = ((X[j] * E.x) % P + P) % P;
		}
		X[i] = (E.y + P) % P;
	}
	gcd %= P;

	ll sum = 0;
	for(int i = 0; i < N; i++) sum = (sum + (A[i] * X[i])) % P;
	assert(sum == gcd);

	//for(int i = 0; i < N; i++) cout << X[i] << ' ';
	for(int m = 0; m < P; m++)
	{
		if((gcd * m) % P == B)
		{
			//cout << m << endl;
			cout << "YES\n";
			for(int i = 0; i < N; i++) cout << (m * X[i]) % P << ' ';
			return 0;
		}
	}
	cout << "NO\n";
}
