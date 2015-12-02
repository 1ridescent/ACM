#include <bits/stdc++.h>

using namespace std;

const int LGMAX = 17;
const int MAX = (1 << LGMAX);
struct SparseTable
{
	pair<int, int> table[LGMAX + 1][MAX];
	void init(pair<int, int> A[MAX])
	{
		for(int i = 0; i < MAX; i++)
			table[0][i] = A[i];
		for(int s = 1; s <= LGMAX; s++)
			for(int i = 0; i <= MAX - (1 << s); i++)
				table[s][i] = max(table[s - 1][i], table[s - 1][i + (1 << (s - 1))]);
	}
	pair<int, int> lookup(int l, int r) // [l, r]
	{
		r++;
		int s = 31 - __builtin_clz(r - l);
		return max(table[s][l], table[s][r - (1 << s)]);
	}
};

int N, Q;
int A[MAX];
pair<int, int> D[MAX];
SparseTable ST;

typedef long long ll;
ll solve(int l, int r)
{
	if(l == r) return 0;
	pair<int, int> p = ST.lookup(l, r - 1);
	ll v = p.first, m = p.second;
	//printf("l=%d r=%d m=%d v=%d\n", l, r, (int)m, (int)v);
	return (m - l + 1) * (r - m) * v + solve(l, m) + solve(m + 1, r);
}

int main()
{
	cin >> N >> Q;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 1; i < N; i++) D[i] = make_pair(abs(A[i] - A[i + 1]), i);
	ST.init(D);
	while(Q--)
	{
		int l, r;
		cin >> l >> r;
		cout << solve(l, r) << endl;
	}
}
