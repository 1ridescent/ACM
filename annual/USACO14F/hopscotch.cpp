#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

struct BIT
{
	vector<int> bit;
	map<int, int> remap;
	void init(vector<int>& X)
	{
		sort(X.begin(), X.end());
		bit = vector<int>(X.size() + 4, 0);
		for(int i = 0; i < X.size(); i++) remap[X[i]] = i + 2;
	}
	void insert(int x, int v)
	{
		//printf("remap[%d] = %d\n", x, remap[x]);
		for(int i = remap[x]; i < bit.size(); i += i & -i)
		{
			bit[i] += v;
			if(bit[i] > mod) bit[i] -= mod;
		}
	}
	int lookup_excl(int x)
	{
		//printf("remap[%d] = %d\n", x, remap[x]);
		int res = 0;
		for(int i = remap[x] - 1; i > 0; i -= i & -i)
		{
			res += bit[i];
			if(res > mod) res -= mod;
		}
		return res;
	}
};

int N, M, K;
int A[755][755];
vector<int> V[563000];
BIT B[563000];

int main()
{
	freopen("hopscotch.in", "r", stdin); freopen("hopscotch.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> N >> M >> K;
	for(int c = 1; c <= M; c++)
		V[0].push_back(c);
	for(int r = 1; r <= N; r++)
		for(int c = 1; c <= M; c++)
		{
			cin >> A[r][c];
			V[A[r][c]].push_back(c);
		}
	for(int i = 0; i <= K; i++)
	{
		if(!V[i].empty())
			B[i].init(V[i]);
	}
	B[0].insert(1, 1);
	B[A[1][1]].insert(1, 1);
	for(int r = 2; r <= N; r++)
		for(int c = M; c >= 2; c--)
		{
			int x = A[r][c];
			int total = B[0].lookup_excl(c);
			//printf("looking up B[%d][%d]\n", x, c);
			int bad = B[x].lookup_excl(c);
			int val = total - bad;
			if(val < 0) val += mod;
			//printf("total[%d][%d] = %d - %d = %d\n", r, c, total, bad, val);
			if(r == N && c == M)
			{
				cout << val << endl;
				return 0;
			}
			B[0].insert(c, val);
			//printf("inserting %d to B[%d][%d]\n", val, x, c);
			B[x].insert(c, val);
		}
}
