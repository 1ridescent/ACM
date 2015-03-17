#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = (1 << 17);

int N;
int A[MAX];
map<int, int> I;
ll K;

ll bit[MAX];
void insert(int i, int v)
{
	i += 10;
	for(; i < MAX; i += i & -i) bit[i] += v;
}
ll lookup(int i)
{
	i += 10;
	ll r = 0;
	for(; i > 0; i -= i & -i) r += bit[i];
	return r;
}
ll seg(int l, int r)
{
	return lookup(r) - lookup(l - 1);
}

int main()
{
	cin >> N >> K;
	for(int i = 1; i <= N; i++)
	{
		cin >> A[i];
		I[A[i]] = -1;
	}
	int id = 0;
	for(map<int, int>::iterator it = I.begin(); it != I.end(); it++)
		it->second = ++id;
	for(int i = 1; i <= N; i++)
		A[i] = I[A[i]];
	//for(int i = 1; i <= N;i ++) cout << A[i] << ' ' ; cout << endl;
	ll ans = 0;
	ll cur = 0;
	int r = 0;
	for(int l = 1; l <= N; l++)
	{
		while(r < l || r < N && cur < K)
		{
			//cout << "old cur = " << cur << endl;
			r++;
			cur += seg(A[r] + 1, 100100);
			insert(A[r], 1);
		}
		//cout << l <<  ' ' << r << ' ' << cur << endl;
		if(cur >= K) ans += N - r + 1;
		cur -= seg(0, A[l] - 1);
		insert(A[l], -1);
	}
	cout << ans << endl;
}
