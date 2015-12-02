#include <bits/stdc++.h>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b)
{
	return (a.first + a.second < b.first + b.second);
}

int N;
pair<int, int> A[200005];
int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		cin >> A[i].first;
		A[i].second = i;
	}
	sort(A, A + N, cmp);
	for(int i = 1; i < N; i++)
		if(!cmp(A[i - 1], A[i]))
		{
			cout << ":(";
			return 0;
		}
	for(int i = 0; i < N; i++)
		if(A[i].first + A[i].second - i < 0)
		{
			cout << ":(";
			return 0;
		}
	for(int i = 0; i < N; i++) cout << A[i].first + A[i].second - i << ' ';
}
