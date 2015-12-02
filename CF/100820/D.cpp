#include <bits/stdc++.h>

using namespace std;

int S[2][3];

void no()
{
	cout << "NO\n";
	exit(0);
}
#define SQ(x) ((x) * (x))

int main()
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 3; j++)
			cin >> S[i][j];
		sort(S[i], S[i] + 3);
	}
	for(int i = 0; i < 3; i++)
		if(S[0][i] != S[1][i]) no();
	if(SQ(S[0][0]) + SQ(S[0][1]) != SQ(S[0][2])) no();
	cout << "YES\n";
}
