#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1000000000;

int N, K;
int A[205];

vector<int> good, bad;

int main()
{
	cin >> N >> K;
	for(int i = 1; i <= N; i++) cin >> A[i];
	int best = -INF;
	for(int l = 1; l <= N; l++)
	{
		for(int r = l; r <= N; r++)
		{
			good.clear();
			bad.clear();
			for(int i = l; i <= r; i++) good.push_back(A[i]);
			for(int i = 1; i < l; i++) bad.push_back(A[i]);
			for(int i = r + 1; i <= N; i++) bad.push_back(A[i]);

			for(int k = 0; k < K; k++)
			{
				int mingood = INF, mingoodi;
				int maxbad = -INF, maxbadi;
				for(int i = 0; i < good.size(); i++)
				{
					if(good[i] < mingood) mingood = good[i], mingoodi = i;
				}
				for(int i = 0; i < bad.size(); i++)
				{
					if(bad[i] > maxbad) maxbad = bad[i], maxbadi = i;
				}
				if(mingood < maxbad)
				{
					swap(good[mingoodi], bad[maxbadi]);
				}
				else break;
			}

			int sum = 0;
			for(int i = 0; i < good.size(); i++) sum += good[i];
			best = max(best, sum);
		}
	}
	cout << best << endl;
	return 0;
}
