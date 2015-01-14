#include <iostream>
#include <cstdio>

using namespace std;

int N, M;
int A[1010], B[1010];

int locate(int a, int b, int t)
{
	int l = b - a;
	t %= (2 * l);
	if(t < l) return a + t;
	t -= l;
	return b - t;
}

int main()
{
	freopen("knockout.in", "r", stdin);
	freopen("knockout.out", "w", stdout);
	cin >> N >> M;
	for(int i = 0; i < N; i++) cin >> A[i] >> B[i];
	while(M--)
	{
		int x, y, t;
		cin >> x >> y >> t;
		int cnt = 0;
		for(int i = 0; i < N; i++)
		{
			int p = locate(A[i], B[i], t);
			if(x <= p && p <= y) cnt++;
		}
		cout << cnt << '\n';
	}
}
