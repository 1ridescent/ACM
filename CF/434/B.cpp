#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define left Left
#define right Right

int N, M, Q;
int A[1010][1010];
int up[1010][1010], down[1010][1010], left[1010][1010], right[1010][1010]; // histograms

int height[1010];
int leftmost[1010], rightmost[1010];
int process(int p, int len)
{
	vector< pair<int, int> > S; // stack (i, height[i])
	for(int i = 1; i <= len; i++)
	{
		leftmost[i] = i;
		while(!S.empty() && S.back().second >= height[i])
		{
			leftmost[i] = S.back().first;
			S.pop_back();
		}
		S.push_back(make_pair(leftmost[i], height[i]));
	}
	S.clear();
	for(int i = len; i >= 1; i--)
	{
		rightmost[i] = i;
		while(!S.empty() && S.back().second >= height[i])
		{
			rightmost[i] = S.back().first;
			S.pop_back();
		}
		S.push_back(make_pair(rightmost[i], height[i]));
	}
	int best = 0;
	for(int i = 1; i <= len; i++)
	{
		//cout << i << ": (" << leftmost[i] << "," << rightmost[i] << ")\n";
		if(leftmost[i] <= p && p <= rightmost[i])
		{
			best = max(best, height[i] * (rightmost[i] - leftmost[i] + 1));
		}
	}
	return best;
}

int main()
{
	/*while(true)
	{
		cin >> N;
		for(int i = 1; i <= N; i++) cin >> height[i];
		cin >> M;
		cout << process(M, N) << endl;
	}*/
	cin >> N >> M >> Q;
	for(int i = 1; i <= N; i++) for(int j = 1; j <= M; j++) cin >> A[i][j];

	memset(left, 0, sizeof(left));
	for(int r = 1; r <= N; r++) for(int c = 1; c <= M; c++) left[r][c] = (A[r][c] ? left[r][c - 1] + 1 : 0);
	memset(up, 0, sizeof(up));
	for(int r = 1; r <= N; r++) for(int c = 1; c <= M; c++) up[r][c] = (A[r][c] ? up[r - 1][c] + 1 : 0);
	memset(right, 0, sizeof(right));
	for(int r = N; r >= 1; r--) for(int c = M; c >= 1; c--) right[r][c] = (A[r][c] ? right[r][c + 1] + 1 : 0);
	memset(down, 0, sizeof(left));
	for(int r = N; r >= 1; r--) for(int c = M; c >= 1; c--) down[r][c] = (A[r][c] ? down[r + 1][c] + 1 : 0);

	while(Q--)
	{
		int t, x, y;
		cin >> t >> x >> y;
		if(t == 1)
		{
			A[x][y] ^= 1;
			int r, c;
			r = x;
			for(c = 1; c <= M; c++) left[r][c] = (A[r][c] ? left[r][c - 1] + 1 : 0);
			for(c = M; c >= 1; c--) right[r][c] = (A[r][c] ? right[r][c + 1] + 1 : 0);
			c = y;
			for(r = 1; r <= N; r++) up[r][c] = (A[r][c] ? up[r - 1][c] + 1 : 0);
			for(r = N; r >= 1; r--) down[r][c] = (A[r][c] ? down[r + 1][c] + 1 : 0);
		}
		else
		{
			int best = 0;
			int r, c;
			r = x;
			for(c = 1; c <= M; c++) height[c] = up[r][c];
			best = max(best, process(y, M));
			for(c = 1; c <= M; c++) height[c] = down[r][c];
			best = max(best, process(y, M));
			c = y;
			for(r = 1; r <= N; r++) height[r] = left[r][c];
			best = max(best, process(x, N));
			for(r = 1; r <= N; r++) height[r] = right[r][c];
			best = max(best, process(x, N));
			cout << best << '\n';
		}
	}
}
