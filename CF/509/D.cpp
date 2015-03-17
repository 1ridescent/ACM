#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e15;

int N, M;
ll A[105][105];

void no()
{
	cout << "NO\n";
	exit(0);
}
void check(bool b)
{
	if(!b) no();
}
ll a[105], b[105];
void final(ll K)
{
	check(K > 0);
	for(int i = 1; i <= N; i++) a[i] = A[i][1];
	for(int j = 1; j <= M; j++) b[j] = (A[1][j] - A[1][1] + K) % K;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			if(A[i][j] >= K || A[i][j] != (a[i] + b[j]) % K) no();
	cout << "YES\n" << K << endl;
	for(int i = 1; i <= N; i++) cout << a[i] << ' ';
	cout<< endl;
	for(int j = 1; j <= M; j++) cout << b[j] << ' ';
	cout << endl;
	exit(0);
}

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			cin >> A[i][j];
	if(N == 1)
	{
		cout << "YES\n" << inf << endl;
		cout << 0 << endl;
		for(int j = 1; j <= M; j++) cout << A[1][j] << ' ';
		cout << endl;
		return 0;
	}
	if(M == 1)
	{
		cout << "YES\n" << inf << endl;
		for(int i = 1; i <= N; i++) cout << A[i][1] << ' ';
		cout << endl;
		cout << 0 << endl;
		return 0;
	}
	for(int r = 2; r <= N; r++)
	{
		for(int i = 1; i <= M; i++)
			for(int j = i + 1; j <= M; j++)
			{
				if(A[1][i] <= A[1][j])
				{
					if(A[r][i] <= A[r][j]) check(A[r][j] - A[r][i] == A[1][j] - A[1][i]);
					else final((A[1][j] - A[1][i]) - (A[r][j] - A[r][i]));
				}
				else if(A[1][i] > A[1][j])
				{
					if(A[r][i] > A[r][j]) check(A[r][i] - A[r][j] == A[1][i] - A[1][j]);
					else final((A[1][i] - A[1][j] - (A[r][i] - A[r][j])));
				}
			}
	}
	final(inf);
}
