#include <iostream>
#include <algorithm>

using namespace std;

int N;
int A[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 0; i < N; i++) cin >> A[i];
	sort(A, A + N);
	int ans = N;
	for(int i = 0; i < N; i++)
	{
		ans = min(ans, A[i] + N - 1 - i);
	}
	cout << ans << endl;
}
