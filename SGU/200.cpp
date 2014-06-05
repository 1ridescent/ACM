#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int R, C;
bool V[105][105];
void gaussian()
{
	for(int t = 1; t <= R && t <= C; t++)
	{
		int s = -1;
		for(int r = t; r <= R; r++) if(V[r][t]) s = r;
		if(s == -1) continue;
		for(int i = 1; i <= C; i++) swap(V[t][i], V[s][i]); // swap rows
		assert(V[t][t]);
		for(int r = 1; r <= R; r++)
		{
			if(r == t) continue;
			if(V[r][t])
			{
				for(int i = 1; i <= C; i++) V[r][i] ^= V[t][i]; // xor
			}
		}
	}
}
void print()
{
	for(int r = 1; r <= R; r++)
	{
		for(int c = 1; c <= C; c++) cout << V[r][c];
		cout << endl;
	}
}
int rank()
{
	gaussian();
	int res = 0;
	for(int r = 1; r <= R && r <= C; r++)
	{
		bool one = false;
		for(int c = 1; c <= C; c++) one |= V[r][c];
		res += one;
	}
	return res;
}

vector<int> primes;

vector<int> add(vector<int>& a, vector<int>& b)
{
	vector<int> c;
	int carry = 0;
	for(int i = 0; i < a.size() || i < b.size(); i++)
	{
		int x = (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0) + carry;
		c.push_back(x % 10);
		carry = x / 10;
	}
	if(carry) c.push_back(carry);
	return c;
}
vector<int> get(int power)
{
	vector<int> zero(1);
	vector<int> one(1, 1);
	if(power == 0) return zero;
	vector<int> res = zero;
	for(int i = 1; i <= power; i++)
	{
		res = add(res, res);
		res = add(res, one);
	}
	return res;
}

int main()
{
	primes.push_back(-1);
	for(int p = 2; p <= 100000; p++)
	{
		bool isprime = true;
		for(int i = 2; i * i <= p; i++)
			if(p % i == 0)
			{
				isprime = false;
				break;
			}
		if(isprime) primes.push_back(p);
	}

	cin >> R >> C;
	for(int c = 1; c <= C; c++)
	{
		int x;
		cin >> x;
		for(int r = 1; r <= R; r++)
		{
			int p = primes[r];
			while(x % p == 0)
			{
				V[r][c] ^= 1;
				x /= p;
			}
		}
	}

	int power = C - rank();
	//cout << power << endl;return 0;
	vector<int> res = get(power);
	for(int i = res.size() - 1; i >= 0; i--) cout << res[i];
	return 0;
}
