#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

struct Trie
{
	Trie* trie[26];
	int cnt[26];
	int last;
	Trie()
	{
		memset(trie, 0, sizeof(trie));
		memset(cnt, 0, sizeof(cnt));
		last = false;
	}
};

int N;
Trie* root;
string S[30030];
vector<string> res;

void insert(string S)
{
	Trie* T = root;
	for(int i = 0; i < S.size(); i++)
	{
		char c = S[i];
		T->cnt[c - 'a']++;
		if(T->cnt[c - 'a'] == 1)
		{
			T->trie[c - 'a'] = new Trie();
		}
		T = T->trie[c - 'a'];
	}
	T->last = true;
}

bool order[26][26]; // [a][b] true : a < b
bool visited[26];
bool valid;
void dfs(int u, int d)
{
	if(d > 26) valid = false;
	if(!valid) return;
	visited[u] = true;
	for(int v = 0; v < 26; v++)
	{
		if(order[u][v]) dfs(v, d + 1);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 0; i < N; i++) cin >> S[i];

	root = new Trie();
	for(int i = 0; i < N; i++) insert(S[i]);

	for(int h = 0; h < N; h++)
	{
		memset(order, 0, sizeof(order));
		memset(visited, 0, sizeof(visited));
		valid = true;

		string s = S[h];
		//cout << "testing " << s << endl;
		Trie* T = root;
		for(int i = 0; i < s.size(); i++)
		{
			if(T->last)
			{
				//cout << "reached end\n";
				valid = false;
			}
			for(int c = 0; c < 26; c++)
			{
				if(c == s[i] - 'a') continue;
				if(T->cnt[c] > 0)
				{
					//cout << s[i] << "->" << (char)(c + 'a') << endl;
					order[s[i] - 'a'][c] = true;
				}
			}
			T = T->trie[s[i] - 'a'];
		}
		for(int c = 0; c < 26; c++)
		{
			memset(visited, 0, sizeof(visited));
			dfs(c, 0);
		}
		if(valid) res.push_back(s);
	}

	cout << res.size() << '\n';
	for(int i = 0; i < res.size(); i++) cout << res[i] << '\n';
	return 0;
}
