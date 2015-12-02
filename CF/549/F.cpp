#include <bits/stdc++.h>

using namespace std;

const int inf = 2e9;

int N, K;
int A[1000500];
int S[1000500];
int cnt[1000500];

long long ans;

void solve(int l, int r)
{
	if(l == r) return;
	int m = (l + r) / 2;
	solve(l, m);
	solve(m + 1, r);
	int a = m, b;
	for(b = m + 1; b <= r; )
	{
		int b2 = b;
		while(b2 <= r && A[b2] <= A[b]) b2++;
		int a2 = a;
		while(a2 >= l && A[a2] <= A[b]) a2--;

		for(int i = a; i > a2; i--) cnt[S[i - 1]]++;
		for(int i = b; i < b2; i++) ans += cnt[(S[i] - A[b] % K + K) % K];

		b = b2;
		a = a2;
	}
	for(int i = m; i > a; i--) cnt[S[i - 1]]--;
	b = m + 1;
	for(a = m; a >= l; a--)
	{
		int a2 = a;
		while(a2 >= l && A[a2] <= A[a]) a2--;
		int b2 = b;
		while(b2 <= r && A[b2] < A[a]) b2++;

		for(int i = b; i < b2; i++) cnt[S[i]]++;
		for(int i = a; i > a2; i--) ans += cnt[(S[i - 1] + A[a]) % K];

		a = a2;
		b = b2;
	}
	for(int i = m + 1; i < b; i++) cnt[S[i]]--;
}

int main()
{
	cin >> N >> K;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 1; i <= N; i++)
		S[i] = (S[i - 1] + A[i]) % K;
	solve(1, N);
	cout << ans;
	for(int i = 0; i < K;i ++) assert(!cnt[i]);
}
