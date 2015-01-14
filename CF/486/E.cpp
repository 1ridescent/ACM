#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include <cstdio>

using namespace std;

const int MAX = (1 << 17);
int bit[2 * MAX];
void init()
{
	memset(bit, 0, sizeof(bit));
}
void insert(int v, int i)
{
	for(; i < MAX; i += i & -i)
		bit[i] = max(bit[i], v);
}
int lookup(int i)
{
	int res = 0;
	for(; i > 0; i -= i & -i)
		res = max(res, bit[i]);
	return res;
}

int N;
int A[100005];
int L[100005];
set<pair<int, int> > S[100005];
vector<int> V[100005];
char ans[100005];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
		cin >> A[i];
	init();
	int M = 0;
	for(int i = 1; i <= N; i++)
	{
		L[i] = 1 + lookup(A[i] - 1);
		insert(L[i], A[i]);
		V[L[i]].push_back(i);
		M = max(M, L[i]);
	}
	memset(ans, '1', sizeof(ans));
	for(int i = N; i >= 1; i--)
	{
		bool include = false;
		if(L[i] == M)
			include = true;
		else if(S[L[i] + 1].upper_bound(make_pair(A[i] + 1, -1)) != S[L[i] + 1].end())
			include = true;
		if(include)
		{
			S[L[i]].insert(make_pair(A[i], i));
			ans[i] = '2';
		}
	}
	for(int i = 1; i <= N; i++)
		if(ans[i] == '2')
			if(S[L[i]].size() == 1)
				ans[i] = '3';
	ans[N + 1] = '\0';
	printf("%s\n", ans + 1);
}
