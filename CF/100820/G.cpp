#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = (1 << 17);

int N, R, W, H;

map<ll, ll> Yid;
pair<ll, ll> P[100005];

int bit[MAX];
void insert(int v, int i)
{
	i = MAX - 3 - i;
	for(; i < MAX; i += i & -i) bit[i] = max(bit[i], v);
}
int lookup(int i)
{
	i = MAX - 3 - i;
	int res = 0;
	for(; i > 0; i -= i & -i) res = max(res, bit[i]);
	return res;
}

int main()
{
	cin >> N >> R >> W >> H;
	for(int i = 0; i < N; i++)
	{
		ll x, y;
		cin >> x >> y;
		x *= R;
		P[i] = make_pair(x + y, y - x);
		Yid[y - x] = -1;
	}
	int next_id = 1;
	for(auto& it : Yid) it.second = next_id++;
	for(int i = 0; i < N; i++) P[i].second = Yid[P[i].second];
//	for(int i = 0; i < N; i++) cout << P[i].first << ' ' << P[i].second << endl;
	sort(P, P + N);
	int ans = 0;
	for(int i = N - 1; i >= 0; i--)
	{
		int r = lookup(P[i].second);
//		cout << P[i].first << ' ' << P[i].second << ' ' << r + 1 << endl;
		ans = max(ans, r + 1);
		insert(r + 1, P[i].second);
	}
	cout << ans << endl;
}
