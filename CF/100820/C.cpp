#include <bits/stdc++.h>

using namespace std;

#define LEN 100
string to_canon(string S)
{
	int i = 0;
	while(S[i] != ':') i++;
	i += 2;
	deque<char> res;
	while(i < S.size())
	{
		if(S[i] == 'u')
		{
			res.push_front('1');
			i += 6;
		}
		else if(S[i] == 'm')
		{
			res.push_front('2');
			i += 7;
		}
		else if(S[i] == 'l')
		{
			res.push_front('3');
			i += 6;
		}
		else if(S[i] == 'c') break;
		else assert(false);
	}
	while(res.size() < LEN) res.push_back('2');
	S = string(LEN, '.');
	for(int i = 0; i < LEN; i++) S[i] = res[i];
	return S;
}

int N;
string S[1005];

int main()
{
	cin >> N;
	string junk;
	getline(cin, junk);
	for(int i = 0; i < N; i++)
	{
		string s;
		getline(cin, s);
		string name = s.substr(0, s.find(':'));
		S[i] = to_canon(s) + name;
		//cout << S[i] << endl;
	}
	sort(S, S + N);
	for(int i = 0; i < N; i++)
	{
		for(int j = LEN; j < S[i].size(); j++) cout << S[i][j];
		cout << '\n';
	}
}
