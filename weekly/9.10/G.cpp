#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int INF = 1000000000;

const int MAX = (1 << 16);
int seg[2 * MAX];
void init()
{
	for(int i = 0; i < 2 * MAX; i++) seg[i] = INF;
}
void insert(int v, int i)
{
	for(i += MAX; i > 0; i /= 2) seg[i] = min(seg[i], v);
}
int lookup2(int l, int r, int p, int a, int b)
{
	if(a >= r || b <= l) return INF;
	if(l <= a && b <= r) return seg[p];
	int m = (a + b) / 2;
	return min(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
}
int lookup(int l, int r)
{
	return lookup2(l, r, 1, 0, MAX);
}

int N, M;
int main()
{
	cin >> N >> M;
	init();
	insert(0, 1);
	for(int i = 0; i < M; i++)
	{
		int l, r;
		scanf("%d %d", &l, &r);
		lookup(l, r + 1);
		insert(lookup(l, r + 1) + 1, r);
	}
	cout << lookup(N, N + 1) << endl;
}
