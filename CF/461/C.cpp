#include <bits/stdc++.h>

using namespace std;

const int MAX = (1 << 18);

struct BIT
{
	int bit[MAX];
	void insert(int v, int i)
	{
		i += 12;
		for(; i < MAX; i += i & -i) bit[i] += v;
	}
	int lookup(int i)
	{
		i += 12;
		int r = 0;
		for(; i > 0; i -= i & -i) r += bit[i];
		return r;
	}
	int seg(int l, int r)
	{
		if(l > r) swap(l, r);
		return lookup(r) - lookup(l - 1);
	}
	int single(int i)
	{
		return seg(i, i);
	}
};
BIT A;

void print(int l, int r)
{
	cout << "A : ";
	if(l < r)
		for(int i = l + 1; i < r; i += 2) cout << A.single(i) << ' ';
	else
		for(int i = l - 1; i > r; i -= 2) cout << A.single(i) << ' ';
	cout << endl;
}

int N, Q;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> Q;
	int l = 0, r = 2 * N;
	for(int i = 1; i < r; i += 2) A.insert(1, i);
	while(Q--)
	{
		int t;
		cin >> t;
		if(t == 2)
		{
			int a, b;
			cin >> a >> b;
			if(l < r) cout << A.seg(l + a * 2, l + b * 2) << '\n';
			else cout << A.seg(l - a * 2, l - b * 2) << '\n';
		}
		else
		{
			int a;
			cin >> a;
			if(l < r)
			{
				int m = l + a * 2;
				if(m - l <= r - m)
				{
					for(int i = 1; i < m - l; i++)
						A.insert(A.single(m - i), m + i);
					l = m;
				}
				else
				{
					for(int i = 1; i < r - m; i++)
						A.insert(A.single(m + i), m - i);
					r = l;
					l = m;
				}
			}
			else
			{
				int m = l - a * 2;
				if(m - r <= l - m)
				{
					for(int i = 1; i < m - r; i++)
						A.insert(A.single(m - i), m + i);
					r = l;
					l = m;
				}
				else
				{
					for(int i = 1; i < l - m; i++)
						A.insert(A.single(m + i), m - i);
					l = m;
				}
			}
			//print(l, r);
		}
	}
}
