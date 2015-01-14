#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = (1 << 20);
const int MOD = 1000000007;

int pow2[MAX];

int N;
int A[MAX];

int num[22][MAX];

int main()
{
	pow2[0] = 1;
	for(int i = 1; i < MAX; i++)
	{
		pow2[i] = 2 * pow2[i - 1];
		if(pow2[i] > MOD) pow2[i] -= MOD;
	}
	cin >> N;
	for(int i = 0; i < N; i++) scanf("%d", A + i);
	memset(num, 0, sizeof(num));
	for(int i = 0; i < N; i++) num[0][A[i]]++;
	for(int i = 1; i <= 20; i++)
	{
		for(int b = 0; b < MAX; b++)
		{
			if(b & (1 << (i - 1))) num[i][b] = num[i - 1][b];
			else num[i][b] = num[i - 1][b] + num[i - 1][b + (1 << (i - 1))];
			if(num[i][b] >= MOD) num[i][b] -= MOD;
		}
	}
	int res = 0;
	for(int b = 0; b < MAX; b++)
	{
		int sign = 1;
		for(int i = 0; i < 20; i++)
			if(b & (1 << i))
				sign *= -1;
		res += sign * pow2[num[20][b]];
		if(res >= MOD) res -= MOD;
		if(res < 0) res += MOD;
	}
	cout << res;
}
