#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

set<int> S;
vector<int> V;
int A[2000200];

int main()
{
	int N;
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		S.insert(x);
	}

	memset(A, 0, sizeof(A));
	int last = 0;
	for(set<int>::iterator it = S.begin(); it != S.end(); it++)
	{
		A[*it] = *it;
	}
	for(int i = 1; i <= 2000020; i++)
		A[i] = max(A[i], A[i - 1]);

	int best = 0;
	for(set<int>::iterator it = S.begin(); it != S.end(); it++)
	{
		int m = *it;
		for(int i = m + m; i <= 2000020; i += m)
		{
			best = max(best, A[i - 1] % m);
		}
	}

	cout << best;
}
