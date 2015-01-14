#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = (1 << 18);
struct MaxSegTree
{
	int seg[2 * MAX];
	MaxSegTree()
	{
		memset(seg, 0, sizeof(seg));
	}
	void insert(int v, int i)
	{
		for(int p = i + MAX; p > 0; p /= 2) seg[p] = max(seg[p], v);
	}
	int lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return max(lookup2(l, r, 2 * p, a, m), lookup2(l, r, 2 * p + 1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r, 1, 0, MAX);
	}
};

int N, M;

MaxSegTree height;
pair<char, int> input[100100];
vector<pair<char, int> > seq[100100];

int cnt = 0;
bool exists[100100];
int level = 0;
vector<int> res;

int main()
{
	memset(exists, 0, sizeof(exists));
	//memset(valid, 0xFF, sizeof(valid));
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= M; i++)
	{
		cin >> input[i].first >> input[i].second;
		if(input[i].first == '-' && !exists[input[i].second])
		{
			seq[input[i].second].push_back(make_pair('+', 0));
			level++;
		}
		exists[input[i].second] = true;
		seq[input[i].second].push_back(make_pair(input[i].first, i));
	}
	height.insert(level, 0);
	for(int i = 1; i <= M; i++)
	{
		level += (input[i].first == '+' ? 1 : -1);
		height.insert(level, i);
	}

	for(int s = 1; s <= N; s++)
	{
		if(!exists[s])
		{
			res.push_back(s);
			continue;
		}
		bool valid = true;
		{
			int l = 0;
			int r = seq[s][0].second;
			if(height.lookup(l, r) > 0) valid = false;
		}
		for(int i = 1; i < seq[s].size(); i++)
		{
			if(seq[s][i].first == '-')
			{
				int l = seq[s][i].second;
				int r = (i + 1 == seq[s].size() ? M + 1 : seq[s][i + 1].second);
				if(height.lookup(l, r) > 0) valid = false;
			}
		}
		if(valid) res.push_back(s);
	}

	/*for(int i = 0; i < M; i++)
	{
		char t;
		cin >> t;
		int x;
		cin >> x;
		if(t == '-')
		{
			if(!exists[x])
			{
				exists[x] = true;
				prev = true;
			}
			else cnt--;
			if(cnt > 0) valid[x] = false;
			else if(cnt == 0) maybe.push_back(x);
		}
		else
		{
			if(!exists[x])
			{
				exists[x] = true;
				maybe.push_back(x);
			}
			cnt++;
		}
	}
	if(prev)
	{
		for(int i = 0; i < maybe.size(); i++) valid[maybe[i]] = false;
	}
	for(int i = 1; i <= N; i++)
	{
		if(!exists[i] || valid[i]) res.push_back(i);
	}*/
	cout << res.size() << '\n';
	for(int i = 0; i < res.size(); i++) cout << res[i] << ' ';
	return 0;
}
