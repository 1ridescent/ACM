#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

int main()
{
	srand(time(0));
	int N, T;
	cin >> N >> T;
	map<vector<int>, int> freq;
	while(T--)
	{
		vector<int> P(N);
		for(int k = 0; k < N; k++) P[k] = k;
		for(int k = 0; k < N; k++)
		{
			int p = k + rand() % (N - k);
			swap(P[k], P[p]);
		}
		freq[P]++;
	}
	for(map<vector<int>, int>::iterator it = freq.begin(); it != freq.end(); it++)
	{
		for(int i = 0; i < N; i++) cout << it->first[i] << ' ';
		cout << " : " << it->second << endl;
	}
}
