#include <bits/stdc++.h>

using namespace std;

bool G[256][256];
bool root[256];
void add(char a, char b)
{
	//cout << a << " -> " << b << endl;
	G[b][a] = true;
	root[a] = false;
}
vector<char> order;
bool vis[256];
void topo(char c, int d)
{
	if(d >= 33)
	{
		cout << "Impossible";
		exit(0);
	}
	for(int i = 'a'; i <= 'z'; i++) if(G[c][i] && !vis[i]) topo(i, d + 1);
	vis[c] = true;
	order.push_back(c);
}

int N;
string S[105];

int main()
{
	memset(root, -1, sizeof(root));
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> S[i];
	for(int i = 1; i <= N; i++)
		for(int j = i + 1; j <= N; j++)
		{
			string s = S[i], t = S[j];
			int p = 0;
			while(true)
			{
				if(p == s.size() || p == t.size())
				{
					if(p == s.size()) break;
					else
					{
						cout << "Impossible";
						return 0;
					}
				}
				if(s[p] != t[p])
				{
					add(s[p], t[p]);
					break;
				}
				p++;
			}
		}
	for(char c = 'a'; c <= 'z'; c++) if(root[c]) topo(c, 0);
	if(order.size() != 26) cout << "Impossible";
	else for(int i = 0; i < order.size(); i++) cout << order[i];
}
