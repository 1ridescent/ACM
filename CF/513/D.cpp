#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 20);
struct SegTree
{
	int seg[2 * MAX];
	int init()
	{
		memset(seg, 0, sizeof(seg));
	}
	int lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return max(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
	}
	int lookup(int l, int r)
	{
		//printf("%d %d %d\n", l, r, lookup2(l, r + 1, 1, 0, MAX));
		return lookup2(l, r + 1, 1, 0, MAX);
	}
	void insert(int v, int i)
	{
		for(i += MAX; i > 0; i /= 2) seg[i] = max(seg[i], v);
	}
};

SegTree S;

int N, K;
vector<int> L[1000005], R[1000005];
int LC[1000005], RC[1000005];

void no()
{
	cout << "IMPOSSIBLE";
	exit(0);
}

void dfs(int l, int r)
{
	//cout << l  << ' ' << r<<endl;
	int root = l;
	l++;
	if(l > r) return;
	if(L[root].empty())
	{
		RC[root] = l;
		dfs(l, r);
		return;
	}
	sort(L[root].begin(), L[root].end());
	int l0 = L[root].front(), l1 = L[root].back();
	l1 = max(l1, S.lookup(l, l1));
	LC[root] = l;
	dfs(l, l1);
	if(l1 + 1 <= r)
	{
		RC[root] = l1 + 1;
		dfs(l1 + 1, r);
	}
}

int start[MAX], end[MAX];
int timestamp = 0;
void get_time(int u)
{
	if(!u) return;
	start[u] = timestamp++;
	get_time(LC[u]);
	get_time(RC[u]);
	end[u] = timestamp++;
}
void check()
{
	get_time(1);
	for(int a = 1; a <= N; a++)
	{
		for(int i = 0; i < L[a].size(); i++)
		{
			int b = L[a][i];
			if(!(start[LC[a]] <= start[b] && end[b] <= end[LC[a]])) no();
		}
		for(int i = 0; i < R[a].size(); i++)
		{
			int b = R[a][i];
			if(!(start[RC[a]] <= start[b] && end[b] <= end[RC[a]])) no();
		}
	}
}

void output(int u)
{
	if(u == 0) return;
	output(LC[u]); cout << u << ' '; output(RC[u]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> K;
	while(K--)
	{
		int a, b;
		string s;
		cin >> a >> b >> s;
		if(s[0] == 'L') L[a].push_back(b);
		else R[a].push_back(b);
		S.insert(b, a);
	}
	dfs(1, N);
	check();
	output(1);
}
