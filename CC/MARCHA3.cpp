#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

const int MAX = (1 << 19);
int bit[MAX];
void insert(int v, int i)
{
	for(; i < MAX; i += i & -i) bit[i] += v;
}
int lookup(int i)
{
	int res = 0;
	for(; i > 0; i -= i & -i) res += bit[i];
	return res;
}
void seg(int l, int r)
{
	//cout << '[' << l << ',' << r << "]\n";
	insert(1, l);
	insert(-1, r + 1);
}

int N;
char t[100005];
int x[100005];
char a[100005];
map<int, int> id;

void reset()
{
	memset(bit, 0, sizeof(bit));
	id.clear();
}

void main2()
{
	reset();
	int N;
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		string s;
		cin >> t[i] >> x[i] >> s;
		a[i] = s[0];
		id[x[i] - 1] = -1;
		id[x[i]] = -1;
		id[x[i] + 1] = -1;
	}
	int nextid = 100;
	for(map<int, int>::iterator it = id.begin(); it != id.end(); it++)
		it->second = nextid++;
	for(int i = 0; i < N; i++)
	{
		x[i] = id[x[i]];
		if(t[i] == '=')
		{
			if(a[i] == 'Y') seg(x[i], x[i]);
			else
			{
				seg(50, x[i] - 1);
				seg(x[i] + 1, 405000);
			}
		}
		if(t[i] == '<')
		{
			if(a[i] == 'Y') seg(50, x[i] - 1);
			else seg(x[i], 405000);
		}
		if(t[i] == '>')
		{
			if(a[i] == 'Y') seg(x[i] + 1, 405000);
			else seg(50, x[i]);
		}
	}
	int best = 0;
	for(int i = 50; i <= 405000; i++) best = max(best, lookup(i));
	cout << N - best << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) main2();
}
