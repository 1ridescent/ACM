#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll A[100005];
ll HL[100005], HR[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 1; i <= N; i++) HL[i] = min(HL[i - 1] + 1, A[i]);
	for(int i = N; i >= 1; i--) HR[i] = min(HR[i + 1] + 1, A[i]);
	ll ans = 0;
	for(int i = 1; i <= N; i++) ans = max(ans, min(HL[i], HR[i]));
	cout << ans;
}
