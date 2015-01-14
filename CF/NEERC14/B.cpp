#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long double ld;

struct burrito
{
	ld g, a, b;
	int id;
};
bool cmp(burrito a, burrito b)
{
	return a.a * b.b > a.b * b.a;
}

int N;
burrito B[100005];

ld ans[100005];

int main()
{
	//freopen("burrito.in", "r", stdin); freopen("burrito.out", "w", stdout);

	cin >> N;
	ld start_a, start_b;
	cin >> start_a >> start_b;
	for(int i = 0; i < N; i++)
	{
		cin >> B[i].g >> B[i].a >> B[i].b;
		B[i].id = i;
	}

	sort(B, B + N, cmp);

	ld leftover = start_b;
	ld cur = 0;
	for(int i = 0; i < N; i++)
	{
		ld amount;
		if(B[i].b < 1e-10) amount = B[i].g;
		else amount = leftover / B[i].b;
		//cout << amount << ' ';
		if(amount > B[i].g) amount = B[i].g;
		leftover -= amount * B[i].b;
		cur += amount * B[i].a;
		ans[B[i].id] = amount;
		//cout << leftover << endl;
	}

	if(cur < start_a - 1e-11) printf("-1 -1\n");
	else
	{
		printf("%.9f %.9f\n", (double)cur, (double)(start_b - leftover));
		for(int i = 0; i < N; i++)
		{
			if(i > 0) printf(" ");
			printf("%.9f", (double)ans[i]);
		}
		printf("\n");
	}
}
