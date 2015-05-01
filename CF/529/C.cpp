#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 18);
const int INF = 1e9;
struct MinSegTree
{
	int seg[2 * MAX];
	void init()
	{
		memset(seg, 0, sizeof(seg));
	}
	void insert(int v, int i)
	{
		i += MAX;
		seg[i] = v;
		for(i /= 2; i > 0; i /= 2)
			seg[i] = min(seg[i * 2], seg[i * 2 + 1]);
	}
	int lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return INF;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return min(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r + 1, 1, 0, MAX);
	}
};
MinSegTree S;

int N, M, K, Q;
struct query
{
	int x1, x2;
	int y1, y2;
};
struct rook
{
	int x, y;
};

rook rooks[MAX];
query queries[MAX];

bool ans[MAX];

vector<int> temp_Q[MAX];
vector<int> temp_R[MAX];
void process()
{
	for(int i = 0; i < MAX; i++)
	{
		temp_Q[i].clear();
		temp_R[i].clear();
	}
	for(int i = 0; i < Q; i++)
		temp_Q[queries[i].x2].push_back(i);
	for(int i = 0; i < K; i++)
		temp_R[rooks[i].x].push_back(rooks[i].y);
	S.init();
	for(int x2 = 1; x2 <= 100005; x2++)
	{
		for(int i = 0; i < temp_R[x2].size(); i++)
			S.insert(x2, temp_R[x2][i]);
		for(int qi = 0; qi < temp_Q[x2].size(); qi++)
		{
			int i = temp_Q[x2][qi];
			int x1 = queries[i].x1;
			int y1 = queries[i].y1, y2 = queries[i].y2;
			//printf("%d %d %d %d: lookup = %d\n",x1,y1,x2,y2,S.lookup(y1,y2));
			if(S.lookup(y1, y2) >= x1) ans[i] = true;
		}
	}
}
void alternate()
{
	//printf("alternating...\n");
	for(int i = 0; i < Q; i++)
	{
		swap(queries[i].x1, queries[i].y1);
		swap(queries[i].x2, queries[i].y2);
	}
	for(int i = 0; i < K; i++)
		swap(rooks[i].x, rooks[i].y);
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M >> K >> Q;
	for(int i = 0; i < K; i++) cin >> rooks[i].x >> rooks[i].y;
	for(int i = 0; i < Q; i++) cin >> queries[i].x1 >> queries[i].y1 >> queries[i].x2 >> queries[i].y2;
	process();
	alternate();
	process();
	for(int i = 0; i < Q; i++) cout << (ans[i] ? "YES\n" : "NO\n");
}
