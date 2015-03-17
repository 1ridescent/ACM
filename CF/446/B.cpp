#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, M, K;
ll P;
ll R[1005], C[1005];
ll KR[1000005], KC[1000005];
priority_queue<ll> QR, QC;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M >> K >> P;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			int x;
			cin >> x;
			R[i] += x;
			C[j] += x;
		}
	for(int i = 1; i <= N; i++)
		QR.push(R[i]);
	for(int i = 1; i <= M; i++)
		QC.push(C[i]);
	for(int i = 1; i <= K; i++)
	{
		ll x = QR.top();
		QR.pop();
		KR[i] = KR[i - 1] + x;
		QR.push(x - M * P);
		x = QC.top();
		QC.pop();
		KC[i] = KC[i - 1] + x;
		QC.push(x - N * P);
	}
	ll best = -1e17;
	for(int r = 0; r <= K; r++)
	{
		int c = K - r;
		ll v = KR[r] + KC[c] - ((ll)r) * c * P;
		best=  max(best, v);
	}
	cout << best;
}
