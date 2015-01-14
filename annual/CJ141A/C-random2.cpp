#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

int f(vector<int> P)
{
	int cnt = 0;
	for(int i = 0; i < P.size(); i++)
		for(int j = i + 1; j < P.size(); j++)
			if(P[i] > P[j])
				cnt++;
	return cnt;
}

int main()
{
	srand(time(0));
	int N, T;
	cin >> N >> T;
	map<int, int> freq;
	while(T--)
	{
		vector<int> P(N);
		for(int k = 0; k < N; k++) P[k] = k;
		for(int k = 0; k < N; k++)
		{
			int p = k + rand() % (N - k);
			swap(P[k], P[p]);
		}
		freq[f(P)]++;
	}
	for(map<int, int>::iterator it = freq.begin(); it != freq.end(); it++)
	{
		cout << it->first;
		cout << " : " << it->second << endl;
	}
}
