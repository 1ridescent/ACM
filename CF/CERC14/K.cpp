#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> item;
#define a first
#define b second

int N, K;
item A[150005];

int best[11];
bool test(int m)
{
	memset(best, -1, sizeof(best));
	best[0] = 0;
	for(int i = 0; i < N; i++)
	{
		for(int k = K; k >= 0; k--)
		{
			if(best[k] == -1) continue;
			int val = best[k] + A[i].b;
			if(A[i].a - val >= m)
			{
				if(best[k + 1] == -1) best[k + 1] = val;
				else best[k + 1] = min(best[k + 1], val);
			}
		}
	}
	return (best[K + 1] != -1);
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--)
	{
		cin >> N >> K;
		for(int i = 0; i < N; i++) cin >> A[i].a >> A[i].b;
		sort(A, A + N);
		int low = 0, high = 1000100;
		while(low + 1 < high)
		{
			int mid = (low + high) / 2;
			if(test(mid)) low = mid;
			else high = mid;
		}
		cout << low << '\n';
	}
}
