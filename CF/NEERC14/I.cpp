#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = (1 << 18);
struct BIT
{
	int bit[MAX];
	void init()
	{
		memset(bit, 0, sizeof(bit));
	}
	void insert(int v, int i)
	{
		for(; i < MAX; i += i & -i)
			bit[i] = max(bit[i], v);
	}
	int lookup(int i)
	{
		int res = 0;
		for(; i > 0; i -= i & -i)
			res = max(res, bit[i]);
		return res;
	}
};

int N;
int P[MAX];

BIT B;

int L[MAX], R[MAX];

int main()
{
	freopen("improvements.in", "r", stdin); freopen("improvements.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin >> N;
	for(int x = 1; x <= N; x++)
	{
		int y;
		cin >> y;
		P[y] = x;
	}

	memset(L, 0, sizeof(L));
	B.init();
	for(int i = 1; i <= N; i++)
	{
		L[i] = B.lookup(P[i]) + 1;
		B.insert(L[i], P[i]);
		L[i] = max(L[i], L[i - 1]);
	}

	memset(R, 0, sizeof(R));
	B.init();
	for(int i = N; i >= 1; i--)
	{
		R[i] = B.lookup(P[i]) + 1;
		B.insert(R[i], P[i]);
		R[i] = max(R[i], R[i + 1]);
	}

	int ans = 0;
	for(int l = 0; l <= N; l++)
	{
		int r = l + 1;
		ans = max(ans, L[l] + R[r]);
	}
	cout << ans << '\n';
}
