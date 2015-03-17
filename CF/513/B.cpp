#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll K;
vector<int> A, B;

int main()
{
	cin >> N >> K;
	K--;
	for(int i = 1; i < N; i++)
	{
		if(K & (1LL << (N - 1 - i))) B.push_back(i);
		else A.push_back(i);
	}
	A.push_back(N);
	for(int i = 0; i < A.size(); i++) cout << A[i]<< ' ';
	for(int i = B.size() - 1; i >= 0; i--) cout << B[i]  << ' ';
}
