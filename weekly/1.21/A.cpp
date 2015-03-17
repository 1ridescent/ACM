#include <iostream>
#include <cstring>
#include <deque>

using namespace std;

const int MAX = (1 << 20);

int bit[MAX];
void init()
{
	memset(bit, 0, sizeof(bit));
}
void insert(int i)
{
	i += 10;
	for(; i < MAX; i += i & -i) bit[i]++;
}
int lookup(int i)
{
	i += 10;
	int r = 0;
	for(; i > 0; i -= i & -i) r += bit[i];
	return r;
}

int A[MAX];

deque<int> I[256];

string S, T;
int main()
{
	ios::sync_with_stdio(false);
	cin >> S >> T;
	for(int i = 0; i < S.size(); i++)
		I[S[i]].push_back(i);
	for(int i = 0; i < T.size(); i++)
	{
		A[i] = I[T[i]].front();
		I[T[i]].pop_front();
	}
	init();
	long long res = 0;
	for(int i = 0; i < T.size(); i++)
	{
		//cout << A[i] << ' ' << lookup(A[i]) << ' ';;
		res += lookup(1000100 - A[i]);
		insert(1000100 - A[i]);
	}
	cout << res << endl;
}
