#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

string N;
ll M;
ll total = 0;

ll process(string s, char nxt)
{
	int num_diff = nxt - 'a';
	if(s.size() < N.size())
	{
		ll res = 1;
		for(int i = 0; i < num_diff; i++)
			res *= min(9, 10 - i);
		return res;
	}
	ll res = 0;
	string t = s;
	int map_to[10]; // a -> 0
	memset(map_to, -1, sizeof(map_to));
	bool mapped[10]; // 0 mapped?
	memset(mapped, 0, sizeof(mapped));
	for(int i = 0; i < s.size(); i++)
	{
		int Nd = N[i] - '0';
		int sd = s[i] - 'a';
		if(map_to[sd] != -1)
		{
			if(map_to[sd] == Nd) continue;
			if(map_to[sd] > Nd) break;

		}
		else
		{
			for(int c = 0; c <= 9; c++)
			{

			}
		}
	}
}

void generate(string s, char nxt, int lft)
{
	if(lft == 0)
	{
		//printf("%s\n", s.c_str());
		total += process(s, nxt);
		return;
	}
	generate(s + nxt, nxt + 1, lft - 1);
	for(char c = 'a'; c < nxt; c++)
		generate(s + c, nxt, lft - 1);
}

int main()
{
	cin >> N >> M;
	if(N == "100000000000")
	{
		total += 100000000000LL % M;
		N = "9999999999";
	}
	for(int l = 1; l <= N.size(); l++)
		generate("", 'a', l);
}
