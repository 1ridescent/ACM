#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

string you;
int need;
int num = 0;
map<string, int> id;
string name[1005];
int M;
bool edge[1005][1005];

int get_id(string s)
{
	if(!id.count(s))
	{
		int k = num;
		num++;
		id[s] = k;
		name[k] = s;
	}
	return id[s];
}

vector<pair<int, string> > out;

int main()
{
	cin >> you;
	cin >> need;
	cin >> M;
	for(int i = 0; i < M; i++)
	{
		string s, t;
		cin >> s >> t;
		int a = get_id(s), b = get_id(t);
		edge[a][b] = edge[b][a] = true;
	}
	int n = id[you];
	for(int f = 0; f < M; f++)
	{
		if(f == n || edge[f][n]) continue;
		int cnt = 0;
		for(int i = 0; i < num; i++)
			if(edge[n][i] && edge[i][f]) cnt++;
		out.push_back(make_pair(-cnt, name[f]));
	}
	sort(out.begin(), out.end());
	for(int i = 0; i < need; i++)
	{
		if(i) cout << ' ';
		cout << out[i].second;
	}
	cout << endl;
}
