#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

bool poss[200];
int N;
vector<int> V;
int main()
{
	cin >> N;
	int k;
	cin >> k;
	V.push_back(0);
	for(int i = 0; i < k; i++)
	{
		int x;
		cin >> x;
		V.push_back(x);
	}
	V.push_back(N);

	memset(poss, 0, sizeof(poss));
	for(int i = 0; i < V.size(); i++)
		for(int j = i + 1; j < V.size(); j++)
		{
			poss[V[j] - V[i]] = true;
		}


	for(int i = 0; i < 200; i++)
		if(poss[i])
			cout << i << ' ';
	cout <<endl;
}
