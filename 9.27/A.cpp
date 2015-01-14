#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void no()
{
	cout << "invalid\n";
	exit(0);
}

void process(vector<int> V)
{
	int cnt = 0;
	for(int i = 0; i < V.size(); i++)
	{
		if(V[i] == '*') cnt++;
	}
	if(cnt >= 2) no();
}

bool inside(int i, int j)
{
	return (1 <= i && i <= 8 && 1 <= j && j <= 8);
}

int main()
{
	char B[11][11];
	for(int i = 1; i <= 8; i++)
		for(int j = 1; j <= 8; j++)
		{
			cin >> B[i][j];
		}
	for(int i = 1; i <= 8; i++)
	{
		vector<int> V;
		for(int j = 1; j <= 8; j++)
		{
			V.push_back(B[i][j]);
		}
		process(V);
	}
	for(int j = 1; j <= 8; j++)
	{
		vector<int> V;
		for(int i = 1; i <= 8; i++) V.push_back(B[i][j]);
		process(V);
	}
	for(int s = 1; s <= 16; s++)
	{
		vector<int> V;
		for(int i = 1; i <= 16; i++)
		{
			if(inside(i, s - i)) V.push_back(B[i][s - i]);
		}
		process(V);
	}
	for(int d = -8; d <= 8; d++)
	{
		vector<int> V;
		for(int i = 1; i <= 8; i++)
		{
			if(inside(i, i + d)) V.push_back(B[i][i + d]);
		}
		process(V);
	}
	cout << "valid\n";
}

