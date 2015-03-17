#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, int> A[100005];
bool bad[100005];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i].first >> A[i].second;
	sort(A + 1, A + 1 + N);
	int m = -123123123;
	for(int i = 1; i <= N; i++)
	{
		if(A[i].second < m) bad[i] = true;
		m = max(m, A[i].second);
	}
	m = 123123123;
	for(int i = N; i >= 1; i--)
	{
		if(A[i].second > m) bad[i] = true;
		m = min(m, A[i].second);
	}
	int cnt = 0;
	for(int i = 1; i <= N; i++) if(!bad[i]) cnt ++;//+= (i*i);
	cout << cnt << endl;
}
