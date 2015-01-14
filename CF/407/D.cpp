#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

#define left Left
#define right Right

int N, M;

int A[404][404];

int prev[404][404];
int next[404][404];
int prev2[404][404];
int next2[404][404];

int right[404][404];
int right2[404][404];

int cur_prev[160016];
int cur_next[160016];
vector<int> fix;

vector<int> prevs[404];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) for(int j = 1; j <= M; j++) cin >> A[i][j];

	for(int i = 0; i < 160016; i++) cur_prev[i] = 0, cur_next[i] = 404;

	int best = 1;
	for(int r = 1; r <= N; r++) // u = 1
	{
		for(int c = 1; c <= M; c++)
		{
			prev[r][c] = cur_prev[A[r][c]];
			cur_prev[A[r][c]] = c;
		}
		for(int c = 1; c <= M; c++) cur_prev[A[r][c]] = 0;
		for(int c = M; c >= 1; c--)
		{
			next[r][c] = cur_next[A[r][c]];
			cur_next[A[r][c]] = c;
			best = max(best, 1 * min(next[r][c] - c, M - c + 1));
		}
		for(int c = 1; c <= M; c++) cur_next[A[r][c]] = 404;
	}

	for(int tr = 1; tr <= N; tr++) for(int c = 1; c <= M; c++) right[tr][c] = 404;
	for(int u = 2; u <= N; u++)
	{
		for(int tr = 1; tr <= N - u + 1; tr++)
		{
			int br = tr + u - 1;
			for(int c = 1; c <= M; c++)
			{
				cur_prev[A[tr][c]] = c;
				fix.push_back(A[tr][c]);
				prev2[tr][c] = max(prev[tr + 1][c], cur_prev[A[br][c]]);
			}
			for(int i = 0; i < fix.size(); i++) cur_prev[fix[i]] = 0;
			fix.clear();
			for(int c = M; c >= 1; c--)
			{
				cur_next[A[tr][c]] = c;
				fix.push_back(A[tr][c]);
				next2[tr][c] = min(next[tr + 1][c], cur_next[A[br][c]]);
			}
			for(int i = 0; i < fix.size(); i++) cur_next[fix[i]] = 404;
			fix.clear();
		}

		for(int tr = 1; tr <= N - u + 1; tr++)
		{
			int br = tr + u - 1;
			for(int c = 1; c <= M; c++)
			{
				right2[tr][c] = min(right[tr][c], next2[tr][c]);
			}

			for(int c = 1; c <= M; c++)
			{
				prevs[prev2[tr][c]].push_back(c);
			}
			for(int c = 1; c <= M; c++)
			{
				for(int i = 0; i < prevs[c].size(); i++)
				{
					right2[tr][c] = min(right2[tr][c], prevs[c][i]);
				}
				prevs[c].clear();
			}
			for(int c = M - 1; c >= 1; c--) right2[tr][c] = min(right2[tr][c], right2[tr][c + 1]);

			for(int c = 1; c <= M; c++) best = max(best, u * min(right2[tr][c] - c, M - c + 1));

			//for(int c = 1; c <= M; c++) printf("%d %d %d: %d\n", u, tr, c, right2[tr][c]);
		}

		memcpy(prev, prev2, sizeof(prev));
		memcpy(next, next2, sizeof(next));
		memcpy(right, right2, sizeof(right));

	}

	cout << best << endl;
	return 0;
}
/*

int A[404][404];
short next[404][404][404]; // up, row, col

short temp[160016];
vector<int> fix;

short right[404];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for(int i = 1; i <= N; i++) for(int j = 1; j <= M; j++) cin >> A[i][j];

	for(int i = 0; i < 160016; i++) temp[i] = 404;
	for(int r = 1; r <= N; r++)
	{
		for(int c = M; c >= 1; c--)
		{
			next[1][r][c] = temp[A[r][c]];
			printf("[%d][%d][%d] = %d\n", 1, r, c, (int)next[1][r][c]);
			temp[A[r][c]] = c;
		}
		for(int c = M; c >= 1; c--) temp[A[r][c]] = 404;
	}
	for(int br = 1; br <= N; br++)
	{
		for(int u = 2; u <= br; u++)
		{
			int tr = br - u + 1;
			for(int c = M; c >= 1; c--)
			{
				temp[A[tr][c]] = c;
				fix.push_back(A[tr][c]);
				next[u][br][c] = min(next[u - 1][br][c], temp[A[br][c]]);
				printf("[%d][%d][%d] = %d\n", u, br, c, (int)next[u][br][c]);
			}
			for(int i = 0; i < fix.size(); i++) temp[fix[i]] = 404;
			fix.clear();
		}
	}

	int best = 1;
	for(int tr = 1; tr <= N; tr++)
	{
		for(int c = 0; c < 404; c++) right[c] = 404;
		for(int br = tr; br <= N; br++)
		{
			int u = br - tr + 1;
			for(int c = 1; c <= M; c++)
			{
				right[c] = min(right[c], next[u][br][c]);
				printf("%d %d %d: %d\n", tr, br, c, right[c]);
				best = max(best, u * (min((int)right[c] - c, M - c + 1)));
			}
		}
	}

	cout << best << endl;
	return 0;
}*/
