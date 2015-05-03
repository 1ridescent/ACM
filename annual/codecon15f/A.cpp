#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

map<string, int> M;

string rev(string s)
{
	for(int i = 0; i < s.size() / 2; i++)
		swap(s[i], s[s.size() - 1 - i]);
	return s;
}

int main()
{
	ios::sync_with_stdio(0);
	int N;
	cin >> N;
	int cnt = 0;
	while(N--)
	{
		string s;
		cin >> s;
		string t = rev(s);
		if(t == s) continue;
		if(M[t])
		{
			cnt++;
			M[t]--;
		}
		else
			M[s]++;
	}
	for(map<string, int>::iterator it = M.begin(); it != M.end(); it++)
	{
		if(it->second)
		{
			cout << "-1\n";
			return 0;
		}
	}
	cout << cnt << endl;
	return 0;
}
