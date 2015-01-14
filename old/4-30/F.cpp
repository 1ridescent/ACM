#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main2()
{
	int T;
	string S;
	cin >> T >> S;
	cout << T << ' ';
	bool biggest = true;
	for(int i = 0; i < S.size() - 1; i++)
	{
		if(S[i] < S[i + 1]) biggest = false;
	}
	if(biggest)
	{
		cout << "BIGGEST\n";
		return 0;
	}

	vector<char> V;
	for(int i = 0; i < S.size(); i++) V.push_back(S[i]);
	next_permutation(V.begin(), V.end());
	for(int i = 0; i < V.size(); i++) cout << V[i];
	cout << '\n';
	return 0;/*
	for(int i = V.size() - 2; i >= 0; i--)
	{
		if(V[i] < V[i + 1])
		{
			char next = V[i];
			int nexti = i;
			for(int j = i + 1; j < V.size(); j++)
			{
				if(next )
			}
		}
	}*/
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++) main2();
}
