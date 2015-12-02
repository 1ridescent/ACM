#include <bits/stdc++.h>

using namespace std;

int N;
int A[100005];

set<pair<int, int> > S;
bool test(int x)
{
	S.clear();
	for(int i = 0; i < N; i++) S.insert(make_pair(A[i], i));
	for(int i = 0; i < N / 2; i++)
	{
		int a = S.begin()->first;
		S.erase(S.begin());
		if(S.lower_bound(make_pair(x - a, -1)) == S.end()) return false;
		S.erase(S.lower_bound(make_pair(x - a, -1)));
	}
	return true;
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> A[i];
	int low = 0, high = 1000005;
	while(low + 1 < high)
	{
		int mid = (low + high) / 2;
		if(test(mid)) low = mid;
		else high = mid;
	}
	cout << low << endl;
}
