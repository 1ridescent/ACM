#include <bits/stdc++.h>

using namespace std;

const int MAX = 110;

int R, C, N, M;

int input[MAX][2];

map<int, int> row_id, col_id;

int num[MAX][MAX];

void pre(int a[MAX][MAX])
{
	for(int r = 1; r <= MAX-3; r++)
		for(int c = 1; c <= MAX-3; c++)
		{
			a[r][c] += a[r-1][c] + a[r][c-1] - a[r-1][c-1];
		}
}
void print(int a[MAX][MAX])
{
	for(int r = 1; r <= MAX-3; r++)
	{
		for(int c = 1; c <= MAX-3; c++)
			cout << a[r][c] << ' ';
		cout << endl;
	}
}
inline int get(int a[MAX][MAX], int r1, int r2, int c1, int c2)
{
	return a[r2][c2] - a[r1-1][c2] - a[r2][c1-1] + a[r1-1][c1-1];
}

int main()
{
	cin >> R >> C >> N >> M;
	for(int i = 1; i <= N + M; i++)
	{
		int r, c;
		cin >> r >> c;
		if(false)//r > R - 5 || c > C - 8)
		{
			input[i][0] = -1;
			continue;
		}
		input[i][0] = r;
		input[i][1] = c;
		row_id[r] = col_id[c] = -1;
	}
	int next_id = 2;
	for(auto& it : row_id) it.second = ++next_id;
	next_id = 2;
	for(auto& it : col_id) it.second = ++next_id;
	for(int i = 1; i <= N; i++)
	{
		if(input[i][0] == -1) continue;
		num[row_id[input[i][0]]][col_id[input[i][1]]]--;
	}
	for(int i = N + 1; i <= N + M; i++)
	{
		if(input[i][0] == -1) continue;
		num[row_id[input[i][0]]][col_id[input[i][1]]]++;
	}
	//print(num);cout<<endl;
	pre(num);
	//print(num);
	int best = 123123123;
	for(int r1 = 1; r1 <= MAX-3; r1++)
		for(int c1 = 1; c1 <= MAX-3; c1++)
			for(int r2 = r1; r2 <= MAX-3; r2++)
				for(int c2 = c1; c2 <= MAX-3; c2++)
				{
					int s = get(num, r1, r2, c1, c2);
					//printf("r1=%d c1=%d r2=%d c2=%d s=%d\n",r1,c1,r2,c2,s);
					s += N;
					if(s < best) best = s;
				}
	cout << best << endl;
}
