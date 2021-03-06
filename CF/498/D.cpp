#include <iostream>

using namespace std;

const int MAX = (1 << 17);

int seg[2 * MAX + 10][65];
void propagate_up(int p)
{
	if(p >= MAX) return;
	for(int i = 0; i < 60; i++)
	{
		int f = seg[p * 2][i];
		seg[p][i] = f + seg[p * 2 + 1][(i + f) % 60];
	}
}
void insert(int a, int l)
{
	int p = l + MAX;
	for(int i = 0; i < 60; i++)
	{
		if(i % a == 0)
			seg[p][i] = 2;
		else
			seg[p][i] = 1;
	}
	for(; p > 0; p /= 2)
		propagate_up(p);
}
int lookup2(int l, int r, int p, int a, int b, int t)
{
	if(a >= r || b <= l) return 0;
	if(l <= a && b <= r) return seg[p][t % 60];
	int m = (a + b) / 2;
	int f = lookup2(l, r, p * 2, a, m, t);
	return f + lookup2(l, r, p * 2 + 1, m, b, t + f);
}
int lookup(int l, int r)
{
	return lookup2(l, r, 1, 0, MAX, 0);
}

int N;
int A[MAX];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> A[i];
		insert(A[i], i);
	}
	int Q;
	cin >> Q;
	while(Q--)
	{
		char t;
		int a, b;
		cin >> t >> a >> b;
		if(t == 'A')
			cout << lookup(a, b) << '\n';
		else
			insert(b, a);
	}
}
