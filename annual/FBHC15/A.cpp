#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

bool is_valid(vector<int> D)
{
	if(D.empty()) return false;
	if(D.size() == 1) return true;
	if(D[0] != 0) return true;
}

int to_int(vector<int> D)
{
	int res = 0;
	for(int i = 0; i < D.size(); i++)
	{
		res *= 10;
		res += D[i];
	}
	return res;
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		string S;
		cin >> S;
		vector<int> V;
		for(int i = 0; i < S.size(); i++)
			V.push_back(S[i] - '0');

		int Min = to_int(V), Max = to_int(V);
		for(int i = 0; i < V.size(); i++)
			for(int j = i + 1; j < V.size(); j++)
			{
				vector<int> W = V;
				swap(W[i], W[j]);
				if(is_valid(W))
				{
					Min = min(Min, to_int(W));
					Max = max(Max, to_int(W));
				}
			}

		printf("Case #%d: %d %d\n",t,  Min, Max);
	}
}
