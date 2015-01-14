#include <iostream>

using namespace std;

const int MAX = (1 << 20);
const int OFFSET = (1 << 19);

typedef long long ll;

ll bit[MAX];
void insert(ll v, int i)
{
	i += OFFSET;
	for(; i < MAX; i += i & -i)
	{
		bit[i] += v;
	}
}
ll lookup2(int i)
{
	i += OFFSET;
	ll res = 0;
	for(; i > 0; i -= i & -i)
	{
		res += bit[i];
	}
	return res;
}
ll lookup(int l, int r) // [l, r]
{
	return lookup2(r) - lookup2(l - 1);
}

int N, X;
int cows[MAX];

int main()
{
	cin >> N >> X;
	for(int i = 0; i < N; i++)
	{
		int h;
		cin >> h;
		cows[i] = (h >= X ? 1 : -1);
	}
	for(int i = 0; i < MAX; i++) bit[i] = 0;
	ll offset = 0;
	ll total = 0;
	for(int i = 0; i < N; i++)
	{
		insert(1, offset);
		offset -= cows[i];
		total += lookup(offset, 100100);
	}
	cout << total << endl;
	return 0;
}
