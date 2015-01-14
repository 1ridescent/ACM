#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N, P;
string S;
vector<string> V;

char next(char a, char b, char s)
{
	cout <<a << ' ' << b << endl;
	for(char c = s; c < 'a' + P; c++)
	{
		if(a == c) continue;
		if(b == c) continue;
		return c;
	}
	return 0;
}

int main()
{
	cin >> N >> P >> S;
	if(P == 1)
	{
		cout << "NO";
		return 0;
	}
	else if(P == 2)
	{
		if(N == 1 && S == "a") cout << "b";
		else if(N == 2 && S != "ba") cout << "ba";
		else cout << "NO";
		return 0;
	}

	S = ".." + S;
	char end = 'a' + P - 1;
	for(int i = 2; i < 2 + N; i++)
	{
		char c = next(S[i - 1], S[i - 2], S[i] + 1);
		if(c == 0) continue;
		string T = S;
		for(int j = i + 1; j < 2 + N; j++)
		{
			T[j] = next(T[j - 1], T[j - 2], 0);
		}
		V.push_back(T.substr(2));
	}
	if(V.empty()) cout << "NO";
	sort(V.begin(), V.end());
	cout << V[0];
}
