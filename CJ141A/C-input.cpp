#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

vector<int> r()
{
	int N = 1000;
	vector<int> P(N);
	for(int k = 0; k < N; k++) P[k] = k;
	for(int k = 0; k < N; k++)
	{
		int p = k + rand() % (N - k);
		swap(P[k], P[p]);
	}
	return P;
}
vector<int> t()
{
	int N = 1000;
	vector<int> P(N);
	for(int k = 0; k < N; k++) P[k] = k;
	for(int k = 0; k < N; k++)
	{
		int p = rand() % N;
		swap(P[k], P[p]);
	}
	return P;
}

int main()
{
	srand(time(0));
	cout << 120 << endl;
	for(int i = 0; i < 60; i++)
	{
		vector<int> P = r();
		cout << 1000 << endl;
		for(int i = 0; i < P.size(); i++) cout << P[i] << ' '; cout << endl;
	}
	for(int i = 0; i < 60; i++)
	{
		vector<int> P = t();
		cout << 1000 << endl;
		for(int i = 0; i < P.size(); i++) cout << P[i] << ' '; cout << endl;
	}
}
