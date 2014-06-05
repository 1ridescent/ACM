#include <iostream>
#include <map>
#include <set>
#include <cstring>

using namespace std;

const int MAXHEADS = 10000;

string heads[MAXHEADS];
map<string, int> id; // id of each head
map<string, int> score; // score for this head
int numid = 1;
void insert(string s)
{
	if(id.find(s) == id.end())
	{
		heads[numid] = s;
		id[s] = numid;
		numid++;
	}
}

int find_id(string s)
{
	while(true)
	{
		if(id.find(s) != id.end()) return id[s];
		s = s.substr(1);
	}
	return 0;
}

int nextid[MAXHEADS][256];
int nextscore[MAXHEADS][256];

int N, K;
set<string> combos;
int dp[MAXHEADS][1313];

int main()
{
	insert("");
	cin >> N >> K;
	for(int i = 0; i < N; i++)
	{
		string s;
		cin >> s;
		combos.insert(s);
		while(1)
		{
			insert(s);
			if(s.size() <= 1) break;
			s = s.substr(0, s.size()-1);
		}
	}
	for(map<string, int>::iterator it = id.begin(); it != id.end(); it++)
	{
		string s = it->first;
		while(1)
		{
			if(combos.find(s) != combos.end())
				score[it->first]++;
			if(s.size() <= 1) break;
			s = s.substr(1);
		}
	}
	for(int i = 0; i < numid; i++)
	{
		for(char c = 'A'; c <= 'C'; c++)
		{
			nextid[i][c] = find_id(heads[i]+c);
			nextscore[i][c] = score[heads[nextid[i][c]]];
			//cout << heads[i] << '+' << c << ": " << heads[nextid[i][c]] << endl;
			//cout << heads[i] << c << ": " << nextscore[i][c] << endl;
		}
	}
	for(int i = 0; i < MAXHEADS; i++) for(int j = 0; j < 1313; j++) dp[i][j] = -123123;
	dp[0][0] = 0;
	int best = 0;
	for(int k = 0; k < K; k++)
	{
		for(int i = 0; i < numid; i++)
		{
			for(char c = 'A'; c <= 'C'; c++)
			{
				dp[k+1][nextid[i][c]] = max(dp[k+1][nextid[i][c]], dp[k][i] + nextscore[i][c]);
				best = max(best, dp[k+1][nextid[i][c]]);
			}
		}
	}
	cout << best << endl;
	return 0;
}
