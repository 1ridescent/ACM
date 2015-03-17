#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int trie[1000005][256];
int next;

void init()
{
	memset(trie[0], -1, sizeof(trie[0]));
	next = 1;
}
int insert(string S)
{
	int l = 0;
	int p = 0;
	for(int i = 0; i < S.size(); i++)
	{
		char c = S[i];
		if(trie[p][c] == -1)
		{
			trie[p][c] = next;
			memset(trie[next], -1, sizeof(trie[next]));
			p = next;
			next++;
		}
		else
		{
			p = trie[p][c];
			l++;
		}
	}
	//cout << "val = " << l << endl;
	return l;
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		int N;
		cin >> N;
		init();
		long long res = 0;
		while(N--)
		{
			string S;
			cin >> S;
			res += min(insert(S) + 1, (int)S.size());
		}
		cout << "Case #" << t << ": " << res << endl;
	}
}
