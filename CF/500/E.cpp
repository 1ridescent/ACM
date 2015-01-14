#include <iostream>
#include <vector>
#include <cstring>
#include <deque>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MAX = (1 << 18);

ll bit[MAX];
ll val[MAX];
void init()
{
	memset(val, 0, sizeof(val));
	memset(bit, 0, sizeof(bit));
}
void insert(ll v, int i)
{
	val[i] += v;
	for(; i < MAX; i += i & -i)
		bit[i] += v;
}
ll lookup(int i)
{
	ll res = 0;
	for(; i > 0; i -= i & -i)
		res += bit[i];
	return res;
}
void reset(int i)
{
	insert(-val[i], i);
}

int N, M;
ll X[MAX], L[MAX];
vector<pair<int, int> > Q[MAX]; // [x] = (y, id)
ll ans[MAX];

ll dist(int i, int j)
{
	return X[j] - (X[i] + L[i]);
}

deque<int> alive;
ll reach[MAX];
void process(int i)
{
	ll r = X[i] + L[i];
	while(!alive.empty())
	{
		int j = alive[0];
		if(r >= X[j])
		{
			reset(j);
			alive.pop_front();
			r = max(r, reach[j]);
		}
		else break;
	}
	if(!alive.empty())
	{
		int j = alive[0];
		reset(j);
		insert(X[j] - r, j);
	}
	reach[i] = r;
	alive.push_front(i);
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i <= N; i++)
		cin >> X[i] >> L[i];
	cin >> M;
	for(int i = 0; i < M; i++)
	{
		int x, y;
		cin >> x >> y;
		Q[x].push_back(make_pair(y, i));
	}

	init();
	for(int x = N; x >= 1; x--)
	{
		process(x);
		//cout << "array: "; for(int i = 1; i <= N; i++) cout << val[i] << ' '; cout << endl;
		//cout << "alive: "; for(int i = 0; i < alive.size(); i++) cout << alive[i] << ' '; cout << endl;
		for(int i = 0; i < Q[x].size(); i++)
		{
			int y = Q[x][i].first;
			ans[Q[x][i].second] = lookup(y);
		}
	}
	for(int i = 0; i < M; i++) cout << ans[i] << '\n';
}
