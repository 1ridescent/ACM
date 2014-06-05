#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

#define LEFT 0
#define RIGHT 1

struct state
{
	int total;
	int prev_left_loc, prev_left_dir, prev_right_loc, prev_right_dir;
};

int N, M, K;
int A[17][17];
int segment[17][17][17]; // [row][left][right]
bool visited[17][17][2][17][2];
state dp[17][17][2][17][2]; // [row][left_loc][left_dir][right_loc][right_dir]

int best_val = -1, best_row, best_left_loc, best_left_dir, best_right_loc, best_right_dir;

int compute(int row, int left_loc, int left_dir, int right_loc, int right_dir, int num_left)
{
	printf("%d %d %d %d %d %d\n", row, left_loc, left_dir, right_loc, right_dir, num_left);
	if(visited[row][left_loc][left_dir][right_loc][right_dir]) return dp[row][left_loc][left_dir][right_loc][right_dir].total;

	state& cur = dp[row][left_loc][left_dir][right_loc][right_dir];
	cur.total = -1;
	visited[row][left_loc][left_dir][right_loc][right_dir] = true;

	if(row == 0 || num_left == 0)
	{
		cur.total = 0;
		return 0;
	}
	/*
	int left_start, left_end;
	if(left_dir == LEFT) left_start = left_loc, left_end = N;
	else left_start = 1, left_end = N;

	int right_start, right_end;
	if(right_dir == RIGHT) right_start = 1, right_end = right_loc;
	else right_start = 1, right_end = N;*/

	int len = right_loc - left_loc + 1;

	for(int prev_left_loc = 1; prev_left_loc <= N; prev_left_loc++)
		for(int prev_left_dir = LEFT; prev_left_dir <= RIGHT; prev_left_dir++)
			for(int prev_right_loc = prev_left_loc; prev_right_loc <= N; prev_right_loc++)
				for(int prev_right_dir = LEFT; prev_right_dir <= RIGHT; prev_right_dir++)
				{
					if(left_loc == LEFT && (prev_left_loc < left_loc || prev_left_dir == RIGHT)) continue;
					if(right_loc == RIGHT && (prev_right_loc > right_loc || prev_right_dir == LEFT)) continue;
					int prev = compute(row - 1, prev_left_loc, prev_left_dir, prev_right_loc, prev_right_dir, num_left - len);
					if(prev > cur.total)
					{
						cur.total = prev;
						cur.prev_left_loc = prev_left_loc, cur.prev_left_dir = prev_left_dir, cur.prev_right_loc = prev_right_loc, cur.prev_right_dir = prev_right_dir;
					}
				}

	cur.total += segment[row][left_loc][right_loc];
	return cur.total;
}

int main()
{
	cin >> N >> M >> K;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			cin >> A[i][j];

	for(int r = 1; r <= N; r++)
		for(int c_start = 1; c_start <= N; c_start++)
			for(int c_end = c_start; c_end <= N; c_end++)
			{
				segment[r][c_start][c_end] = 0;
				for(int c = c_start; c <= c_end; c++) segment[r][c_start][c_end] += A[r][c];
			}

	memset(visited, 0, sizeof(visited));

	int best = 0;
	for(int row = 1; row <= N; row++)
		for(int c_start = 1; c_start <= N; c_start++)
			for(int c_end = c_start; c_end <= N; c_end++)
			{
				int len = c_end - c_start + 1;
				if(len > K) continue;
				int total = compute(row, c_start, RIGHT, c_end, LEFT, K);
				if(total > best) best = total;
			}

	cout << best << endl;
	return 0;
}
