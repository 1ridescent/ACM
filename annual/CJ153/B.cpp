#include <bits/stdc++.h>

using namespace std;

const int inf = 2e9;

int N, K;
int A[1005];

int mane()
{
	cin >> N >> K;
	for(int i = 1; i <= N-  K + 1; i++) cin >> A[i];
	vector<int> V;
	int S = A[1];
	for(int s = 1; s <= K; s++)
	{
		int curval = 0, curmax = 0, curmin = 0;
		for(int i = s; i <= N - K; i += K)
		{
			curval += A[i + 1] - A[i];
			curmax = max(curmax, curval);
			curmin = min(curmin, curval);
		}
		S -= curmin;
		V.push_back(curmax - curmin);
	}
	sort(V.begin(), V.end());
	int r = S % K;
	if(r < 0) r += K;
	for(int i = 0; i < V.size() - 1; i++)
		r -= V.back() - V[i];
	cout << V.back() + (r > 0) << '\n';
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cout << "Case #" << t << ": ";
		mane();
	}
}
