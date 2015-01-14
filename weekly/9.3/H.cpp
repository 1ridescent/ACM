#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

typedef long long ll;

const int MAX = (1 << 20);
int bit[MAX];
void init()
{
	memset(bit, 0, sizeof(bit));
}
void insert(int v, int i)
{
	for(; i < MAX; i += i & -i) bit[i] += v;
}
int lookup(int i)
{
	int res = 0;
	for(; i > 0; i -= i & -i) res += bit[i];
	return res;
}

int N;
char S[MAX], T[MAX];
deque<int> D[256];
int A[MAX];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> S[i];
		D[S[i]].push_back(i);
	}
	for(int i = 1; i <= N; i++)
	{
		cin >> T[i];
		A[i] = D[T[i]].front();
		D[T[i]].pop_front();
	}

	long long invs = 0;
	init();
	for(int i = N; i >= 1; i--)
	{
		invs += lookup(A[i]);
		insert(1, A[i]);
	}

	cout << invs << endl;
}
