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
	int N = 1000;
	vector<int> P(N);
	for(int k = 0; k < N; k++) P[k] = k;
	for(int k = 0; k < N; k++)
	{
		int p = k + rand() % (N - k);
		swap(P[k], P[p]);
	}

	cout << N << endl;
	for(int i = 0; i < N; i++) cout << P[i] << ' ';
	cout << endl;
}
