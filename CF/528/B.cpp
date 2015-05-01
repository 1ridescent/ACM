#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = (1 << 19);

map<ll, int> remap;

int N;
ll S[MAX], T[MAX];
vector<int> from[MAX];

int bit[MAX];
void insert(int v, int i)
{
	for(; i < MAX; i += i & -i) bit[i] = max(bit[i], v);
}
int lookup(int i)
{
	int res = 0;
	for(; i > 0; i -= i & -i) res = max(res, bit[i]);
	return res;
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		ll x, w;
		cin >> x >> w;
		S[i] = x - w, T[i] = x + w;
		remap[S[i]] = remap[T[i]] = -1;
	}
	int next = 20;
	for(map<ll, int>::iterator it = remap.begin(); it != remap.end(); it++)
		it->second = next++;
	for(int i = 0; i < N; i++)
	{
		int s = remap[S[i]], t = remap[T[i]];
		from[t].push_back(s);
	}
	for(int t = 10; t < MAX; t++)
	{
		int r = 0;
		for(int i = 0; i < from[t].size(); i++)
		{
			int s = from[t][i];
			//printf("%d %d\n", s, t);
			r = max(r, 1 + lookup(s));
		}
		//if(r) printf("%d %d\n", r, t);
		insert(r, t);
	}
	cout << lookup(MAX - 1) << '\n';
}
