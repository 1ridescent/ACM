#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = (1 << 19);

ll seg[2 * MAX];
void init()
{
	memset(seg, 0, sizeof(seg));
}
void insert(ll v, int i)
{
	i += MAX;
	seg[i] = v;
	for(int p = i / 2; p > 0; p /= 2) seg[p] = max(seg[p * 2], seg[p * 2 + 1]);
}
ll lookup(int l, int r, int p = 1, int a = 0, int b = MAX)
{
	if(a >= r || b <= l) return 0;
	if(l <= a && b <= r) return seg[p];
	int m = (a + b) / 2;
	return max(lookup(l, r, p * 2, a, m), lookup(l, r, p * 2 + 1, m, b));
}

struct query
{
	ll a, b;
	ll z;
	int i;
};

int N, M;
ll A[MAX];
vector<int> modify[MAX];
vector<query> Q[MAX]; // a, b, i
ll ans[MAX];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> A[i];
	for(int i = 1; i < N; i++)
		for(int j = 1; j <= A[i] - A[i + 1]; j++)
			modify[j].push_back(i);
	for(int i = 1; i <= M; i++)
	{
		query q;
		cin >> q.a >> q.b >> q.z;
		q.i = i;
		if(q.z > N) Q[0].push_back(q);
		else Q[q.z].push_back(q);
	}
	init();
	for(int i = 0; i < Q[0].size(); i++)
	{
		query q = Q[0][i];
		ans[q.i] = A[q.b] + q.b * q.z - (q.a - 1) * q.z;
	}
	for(ll m = 1; m <= N; m++)
	{
		for(int j = 0; j < modify[m].size(); j++)
		{
			int i = modify[m][j];
			insert(A[i] + m * i, i);
		}
		for(int i = 0; i < Q[m].size(); i++)
		{
			query q = Q[m][i];
			ans[q.i] = max(A[q.b] + q.b * m, lookup(q.a, q.b + 1)) - (q.a - 1) * m;
		}
		for(int j = 0; j < modify[m].size(); j++)
		{
			int i = modify[m][j];
			insert(0, i);
		}
	}
	for(int i = 1; i <= M; i++) cout << ans[i] << '\n';
}
