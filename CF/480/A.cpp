#include <iostream>
#include <algorithm>

using namespace std;

int N;
pair<int, int> A[5005];

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
		cin >> A[i].second >> A[i].first;
	sort(A, A + N);
	int best = A[N - 1].first;
	int last = -1;
	for(int i = 0; i < N; i++)
	{
		bool good = true;
		if(A[i].first < last)
			good = false;
		for(int j = i + 1; j < N; j++)
			if(A[j].second < A[i].second)
				good = false;
		if(!good)
		{
			best = max(best, A[i].second);
			last = max(last, A[i].second);
		}
	}
	cout << best;
}
