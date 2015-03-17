#include <iostream>
#include <cstring>

using namespace std;

const int inf = 1e9;

int N, K;
int A[17][17];

bool test(int x, int b)
{
	int cur[17];
	memset(cur, 0, sizeof(cur));
	int n = __builtin_popcount(b);
	int r = 0, k = 0;
	while(k <= K - n)
	{
		int p = 0;
		bool over = false;
		for(int c = 0; c < N; c++)
		{
			cur[p] += A[r][c];
			if(cur[p] > x) over = true;
			if(b & (1 << c)) p++;
		}
		if(over)
		{
			k++;
			memset(cur, 0, sizeof(cur));
			continue;
		}
		r++;
		if(r == N) return true;
	}
	return false;
}

bool test_all(int x)
{
	for(int b = 0; b < (1 << (N - 1)); b++)
		if(test(x, b))
			return true;
	return false;
}

int main()
{
	cin >> N >> K;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin >> A[i][j];
	int low = -1, high = inf;
	while(low + 1 < high)
	{
		int mid = (low + high) / 2;
		if(test_all(mid)) high = mid;
		else low = mid;
	}
	cout << high << endl;
}
