#include <bits/stdc++.h>

using namespace std;

const int MAX = 333333;

map<char, int> to[MAX];
int link[MAX], que[MAX], size = 1;

int id[MAX];

void add_str(string s, int idx)
{
	int v = 0;
	for(int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if(c == '$') id[v] = idx;
		if(!to[v][c]) to[v][c] = size++;
		v = to[v][c];
	}

}
void push_links()
{
	link[0] = -1;
	int start = 0, finish = 1;
	que[0] = 0;
	while(start < finish)
	{
		int v = que[start++];
		for(map<char, int>::iterator it = to[v].begin(); it != to[v].end(); it++)
		{
			int u = it->second;
			int c = it->first;
			int j = link[v];
			while(j != -1 && !to[j][c]) j = link[j];
			if(j != -1) link[u] = to[j][c];
			que[finish++] = u;
		}
	}
}

bool cmp(string& s, string& t)
{
	return s.size() > t.size();
}

string T;
int N;
string S[MAX];
int P[MAX];
vector<char> V;
int main()
{
	ios::sync_with_stdio(false);
	freopen("censor.in", "r", stdin); freopen("censor.out", "w", stdout);
	cin >> T >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> S[i];
		S[i] += '$';
	}
	//sort(S + 1, S + 1 + N);
	for(int i = 1; i <= N; i++)
	{
		//cout << "string " << i << " = " << S[i] << endl;
		add_str(S[i], i);
	}
	push_links();
	int p = 0;
	P[0] = 0;
	for(int i = 0; i < T.size(); i++)
	{
		char c = T[i];
		while(p && !to[p][c]) p = link[p];
		if(to[p][c]) p = to[p][c];
		V.push_back(c);
		P[V.size()] = p;
		if(id[p])
		{
			//printf("found string %d at index %d\n", id[p], i);
			int si = S[id[p]].size() - 1;
			while(si--) V.pop_back();
			p = P[V.size()];
		}
	}
	for(int i = 0; i < V.size(); i++) cout << V[i];
	cout << endl;
}

/*int main()
{
	add_str("abcd");
	push_links();
	string text = "abcabbbabcd";
	int p = 0;
	for(int i = 0; i < text.size(); i++)
	{
		char c = text[i];
		printf("text[%d] = %c:\n", i, c);
		if(p && !to[p][c])
		{
			printf("suffix link %d -> %d\n", p, link[p]);
			p = link[p];
		}
		if(to[p][c])
		{
			printf("advance %d -> %d\n", p, to[p][c]);
			p = to[p][c];
		}
	}
}*/
