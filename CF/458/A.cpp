#include <iostream>
#include <deque>
#include <cstdio>
#include <cstdlib>

using namespace std;

void ss()
{
	cout << '>';
	exit(0);
}
void tt() { cout << '<'; exit(0); }
void st() { cout << '='; exit(0); }

deque<int> S, T;

void fix(deque<int>& D)
{
	for(int i = 2; i < D.size(); i++)
	{
		if(D[i - 2] == 0 && D[i - 1] == 1 && D[i] == 1)
		{
			D[i - 2] = 1;
			D[i - 1] = 0;
			D[i] = 0;
		}
		int j = i;
		i -= 2;
		while(i >= 2 && D[i - 2] == 0 && D[i - 1] == 1 && D[i] == 1)
		{
			D[i - 2] = 1;
			D[i - 1] = 0;
			D[i] = 0;
			i -= 2;
		}
		i = j;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	string s, t;
	cin >> s >> t;
	for(int i = 0; i < s.size(); i++) S.push_back(s[i] == '1');
	for(int i = 0; i < t.size(); i++) T.push_back(t[i] == '1');
	while(S.size() < T.size()) S.push_front(0);
	while(T.size() < S.size()) T.push_front(0);
	S.push_front(0);
	T.push_front(0);

	fix(S);
	fix(T);
	for(int i = 0; i < S.size(); i++)
	{
		if(S[i] < T[i]) tt();
		if(S[i] > T[i]) ss();
	}
	st();
}
