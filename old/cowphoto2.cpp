#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int N;
int A[20020];
map<int, int> index[5];
int res[20020];

bool cmp(int a, int b)
{
	int cnt = 0;
	for(int i = 0; i < 5; i++)
	{
		cnt += (index[i][a] < index[i][b]);
	}
	return (cnt >= 3);
}

int main()
{
	cin >> N;
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < N; j++)
		{
			int x;
			cin >> x;
			A[j] = x;
			index[i][x] = j;
		}
	}
	sort(A, A+N, cmp);
	for(int i = 0; i < N; i++) cout << A[i] << '\n';
	return 0;
}
