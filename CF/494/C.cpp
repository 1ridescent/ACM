#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll inf = 1e15;

const int MAX = (1 << 17);
struct MaxSegTree
{
    ll seg[2 * MAX];
    MaxSegTree()
    {
        for(int i = 0; i < 2 * MAX; i++) seg[i] = -inf;
    }
    void insert(ll v, int i)
    {
        for(i += MAX; i > 0; i /= 2) seg[i] = max(seg[i], v);
    }
    ll lookup2(int l, int r, int p, int a, int b)
    {
        if(l >= b || r <= a) return -inf;
        if(l <= a && b <= r) return seg[p];
        int m = (a + b) / 2;
        return max(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
    }
    ll lookup(int l, int r)
    {
        return lookup2(l, r + 1, 1, 0, MAX);
    }
};


int N, Q;
ll A[100005];
MaxSegTree segA;

struct seg
{
	int l, r;
	double p;
	ll maxval;
	bool inside(seg& b)
	{
		return (b.l <= l && r <= b.r);
	}
};
bool cmp(seg a, seg b)
{
	return (a.r - a.l) < (b.r - b.l);
}
seg S[5050];

vector<int> nest[5050];

double dp[5050][10100];

double prob[10100];

int main()
{
	ios::sync_with_stdio(false);

	cin >> N >> Q;
	for(int i = 1; i <= N; i++) cin >> A[i];
	A[++N] = 0;
	ll highest = A[1];
	for(int i = 1; i <= N; i++) highest = max(highest, A[i]);
	ll subtract = highest - 5025;
	for(int i = 1; i <= N; i++)
	{
		A[i] -= subtract;
		A[i] = max(A[i], 0LL);
	}
	for(int i = 1; i <= N; i++) segA.insert(A[i], i);

	for(int i = 0; i < Q; i++)
	{
		cin >> S[i].l >> S[i].r >> S[i].p;
		S[i].maxval = segA.lookup(S[i].l, S[i].r);
	}
	S[Q].l = 1, S[Q].r = N, S[Q].p = 0;
	S[Q].maxval = segA.lookup(S[Q].l, S[Q].r);
	Q++;

	sort(S, S + Q, cmp);

	for(int i = 0; i < Q - 1; i++)
	{
		for(int j = i + 1; j < Q; j++)
		{
			if(S[i].inside(S[j]))
			{
				nest[j].push_back(i);
				break;
			}
		}
	}

	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < Q; i++)
	{
		int m = S[i].maxval;
		double p = S[i].p;
		if(nest[i].empty())
		{
			for(int i = 0; i <= 10050; i++) prob[i] = 0;
			prob[m] = 1;
		}
		else
		{
			for(int k = 0; k <= 10050; k++) prob[k] = 1;
			for(int jj = 0; jj < nest[i].size(); jj++)
			{
				int j = nest[i][jj];
				for(int k = 0; k <= 10050; k++)
					prob[k] *= dp[j][k];
			}
			for(int k = 10050; k > 0; k--)
				prob[k] -= prob[k - 1];

			for(int k = 0; k < m; k++)
			{
				prob[m] += prob[k];
				prob[k] = 0;
			}
		}

		dp[i][0] = prob[0] * (1 - p);
		for(int k = 1; k <= 10050; k++)
			dp[i][k] = prob[k] * (1 - p) + prob[k - 1] * p;

		if(i == Q - 1)
		{
			double res = 0;
			for(int k = 0; k <= 10050; k++)
			{
				res += k * dp[i][k];
			}
			res += subtract;
			printf("%.9f\n", res);
			return 0;
		}

		for(int k = 1; k <= 10050; k++)
			dp[i][k] += dp[i][k - 1];
	}
}
