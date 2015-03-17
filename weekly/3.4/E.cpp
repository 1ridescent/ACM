#include <bits/stdc++.h>

using namespace std;

int N;
bool board[305][305];

bool temp[305][305];
void segments(int row)
{
	memset(temp, -1, sizeof(temp));
	for(int i = 1; i <= N; i++)
		for(int j = i; j <= N; j++)
		{
			temp[i][j] = (temp[i][j - 1] && board[row][j]);
		}
}

int cur[305][305];
void process(int row)
{
	segments(row);
	for(int i = 1; i <= N; i++)
		for(int j = i; j <= N; j++)
		{
			if(cur[i][j] != -1)
			{
				if(board[row][i] && board[row][j]) cur[i][j]++;
				else cur[i][j] = -1;
			}

			if(temp[i][j] && cur[i][j] == -1)
				cur[i][j] = 0;

			//if(row == 4) cout << i << ' ' << j << ' ' << cur[i][j] << endl;
		}
}

int up[305][305][305];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
		{
			char c;
			cin >> c;
			board[i][j] = (c == '.');
		}
	memset(cur, -1, sizeof(cur));
	for(int r = 1; r <= N; r++)
	{
		process(r);
		for(int i = 1; i <= N; i++)
			for(int j = i + 2; j <= N; j++)
			{
				if(temp[i][j] && cur[i][j] >= 2)
					up[r][i][j] = (j - i - 1) * (cur[i][j] - 1);
				//if(r == 4) printf("%d %d %d %d\n",i,j,cur[i][j],up[r][i][j]);

			}
		for(int s = 2; s <= N; s++)
			for(int i = 1; i + s <= N; i++)
			{
				int j = i + s;
				up[r][i][j] = max(up[r][i][j], max(up[r][i + 1][j], up[r][i][j - 1]));
				//if(r == 4) printf("%d %d %d %d\n",i,j,cur[i][j],up[r][i][j]);
			}

	}
	//while(true){int r,i,j;cin>>r>>i>>j;cout<<up[r][i][j]<<endl;}
	int best = -1;
	memset(cur, -1, sizeof(cur));
	for(int r = N; r >= 1; r--)
	{
		process(r);
		for(int i = 1; i <= N; i++)
			for(int j = i + 2; j <= N; j++)
			{
				//if(r == 4) printf("%d %d %d %d\n",i,j,cur[i][j],up[r][i][j]);
				if(temp[i][j] && cur[i][j] >= 2 && up[r][i][j])
				{
					//cout << r << ' ' << i << ' ' << j << ' ' << (cur[i][j] - 1) * (j - i - 1) * up[r][i][j] << endl;
					best = max(best, (cur[i][j] - 1) * (j - i - 1) * up[r][i][j]);
				}
			}
	}
	cout << best << endl;
}
