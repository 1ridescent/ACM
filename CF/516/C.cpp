#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = (1 << 18);

class data
{
public:
	ll within, left, right, len;
};

int N;
ll H[MAX + 10];
ll D[MAX + 10];

data Merge(data a, data b)
{
	data c;
	c.len = a.len + b.len;
	c.left = max(a.left, a.len + b.left);
	c.right = max(a.right + b.len, b.right);
	c.within = max(max(a.within, b.within), a.right + b.left);
	return c;
}

data seg[2 * MAX + 10];
void process(int p, int a, int b)
{
	if(a + 1 == b)
	{
		seg[p].len = D[a];
		seg[p].within = H[a] + D[a] + H[a + 1];
		seg[p].left = D[a] + H[a + 1];
		seg[p].right = D[a] + H[a];
		return;
	}
	int m = (a + b) / 2;
	int pam = p * 2, pmb = p * 2 + 1;
	process(pam, a, m);
	process(pmb, m, b);
	seg[p] = Merge(seg[pam], seg[pmb]);
	//if(1 <= a && b <= N) cout << a << ' ' << b << " : " << seg[p].within << endl;
}
data lookup2(int l, int r, int p, int a, int b)
{
	if(a >= r || b <= l)
	{
		data null;
		null.within = null.left = null.right = null.len = 0;
		return null;
	}
	if(l <= a && b <= r) return seg[p];
	int m = (a + b) / 2;
	return Merge(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
}
data lookup(int l, int r)
{
	return lookup2(l, r, 1, 0, MAX);
}

int main()
{
	ios::sync_with_stdio(false);
	int M;
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
	{
		cin >> D[i];
		D[i + N] = D[i];
	}
	for(int i = 1; i <= N; i++)
	{
		cin >> H[i];
		H[i] *= 2;
		H[i + N] = H[i];
	}
	process(1, 0, MAX);
	/*while(true)
	{
		int a, b;
		cin >> a >> b;
		cout << lookup(a, b).within << endl;
	}*/
	while(M--)
	{
		int a, b;
		cin >> a >> b;
		if(a > b)
		{
			int l = b + 1, r = a - 1;
			cout << lookup(l, r).within << '\n';
		}
		else
		{
			int r = a - 1, l = b + 1;
			cout << lookup(l, r + N).within << '\n';
		}
	}
}
