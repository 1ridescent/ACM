#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M, K;
ll A[100005], B[100005];
ll L[100005], R[100005];

pair<int, int> E[100005];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M >> K;
	ll ans = 0;
	for(int i = 1; i <= N; i++)
	{
		cin >> A[i];
		L[i] = A[i];
		ans = max(ans, L[i]);
		//cout << "input " << A[i] << endl;
	}
	for(int i = 1; i <= M; i++)
	{
		cin >> B[i];
		R[i] = B[i];
		ans = max(ans, R[i]);
	}
	for(int i = 0; i < K; i++) cin >> E[i].first >> E[i].second;
	sort(E, E + K);
	for(int i = 0; i < K; i++)
	{
		int a = E[i].first, b = E[i].second;
		ll temp = max(L[a], R[b] + A[a]);
		R[b] = max(R[b], L[a] + B[b]);
		L[a] = max(L[a], temp);
		//cout << a << ' ' << b << " : " << L[a] << ' ' << R[b] << endl;
		ans = max(ans, max(L[a], R[b]));
	}
	cout << ans << endl;
}
