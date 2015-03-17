#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <cassert>
#include <vector>

using namespace std;

const int MAX = (1 << 20);

struct SegTree
{
	int seg[2 * MAX];
	map<int, int> pos;
	void init()
	{
		memset(seg, 0, sizeof(seg));
	}
	void modify(int v, int i)
	{
		//cout << "modifying " << v << ' ' << i << endl;
		pos[i] = v;
		if(pos[i] == 0) pos.erase(i);
		seg[i + MAX] = v;
		for(int p = (i + MAX) / 2; p > 0; p /= 2)
			seg[p] = max(seg[p * 2], seg[p * 2 + 1]);
	}
	int val(int i)
	{
		return seg[i + MAX];
	}
	int first(int v)
	{
		//cout << "finding first of " << v << endl;
		if(seg[1] < v) return -1;
		int p;
		for(p = 1; p < MAX; )
		{
			//cout << "at " << p << ", val = " << seg[p] << endl;
			if(seg[p * 2] >= v) p = p * 2;
			else p = p * 2 + 1;
		}
		return p - MAX;
	}
	int Left(int i)
	{
		map<int, int>::iterator it = pos.upper_bound(i);
		if(it == pos.begin()) return -1;
		return (--it)->first;
	}
	void print()
	{
		//for(int i = 0; i < 2 * MAX; i++) cout << seg[i] << ' '; cout << endl;
		for(map<int, int>::iterator it = pos.begin(); it != pos.end(); it++)
			cout << it->first << ":" << it->second << ' ';
		cout << endl;
	}
};

int N, M;
SegTree S;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	S.init();
	S.modify(N, 1);
	int lost = 0;
	while(M--)
	{
		char t;
		cin >> t;
		if(t == 'A')
		{
			int size;
			cin >> size;
			int ind = S.first(size);
			if(ind == -1)
			{
				lost++;
				continue;
			}
			int limit = S.val(ind);
			assert(limit >= size);
			//cout << "ind = " << ind << ", size = " << size << endl;
			S.modify(0, ind);
			S.modify(limit - size, ind + size);
		}
		else
		{
			int a, b;
			cin >> a >> b;
			int l = a, r = b;
			int prev = S.Left(a);
			if(prev != -1 && prev + S.val(prev) >= l)
				l = prev;
			int next = S.Left(b);
			if(next != -1 && next + S.val(next) - 1 >= r)
				r = next + S.val(next) - 1;
			vector<int> del;
			map<int, int>::iterator it = S.pos.lower_bound(l);
			while(it != S.pos.end() && it->first <= r)
			{
				del.push_back(it->first);
				it++;
			}
			//cout << "asdf" << endl;
			for(int i = 0; i < del.size(); i++)
				S.modify(0, del[i]);
			del.clear();
			S.modify(r - l + 1, l);
			//cout << "asdfdf" << endl;
		}
		//S.print();
	}
	cout << lost << endl;
}
