#include <iostream>
#include <queue>

using namespace std;

int best[1<<9][1<<6][1<<6]; // [box][row][col]

struct queue_int
{
	int A[3000000];
	int head;
	int tail; // [tail, head)
	queue_int()
	{
		head = 0;
		tail = 0;
	}
	bool empty()
	{
		/*if(head % 10000 == 0)
		{
			cout << head << endl;
		}*/
		return (head == tail);
	}
	void push(int x)
	{
		A[head++] = x;
	}
	int pop()
	{
		return A[tail++];
	}
};
queue_int Q;

int main()
{
	for(int i = 0; i < (1<<9); i++)
		for(int j = 0; j < (1<<6); j++)
			for(int k = 0; k < (1<<6); k++)
				best[i][j][k] = -1;
	string board[9];
	for(int i = 0; i < 9; i++) cin >> board[i];
	int startb = 0, startr = 0, startc = 0;
	for(int b = 0; b < 9; b++)
	{
		int br = b/3, bc = b%3;
		for(int r = 3*br; r < 3*br+3; r++)
			for(int c = 3*bc; c < 3*bc+3; c++)
				if(board[r][c] == '1') startb ^= (1<<b);
	}
	for(int r = 0; r < 9; r++)
	{
		if(r % 3 == 2) continue;
		for(int c = 0; c < 9; c++) if(board[r][c] == '1') startr ^= (1<<(r-r/3));
	}
	for(int c = 0; c < 9; c++)
	{
		if(c % 3 == 2) continue;
		for(int r = 0; r < 9; r++) if(board[r][c] == '1') startc ^= (1<<(c-c/3));
	}
	best[startb][startr][startc] = 0;
	Q.push(startb*(1<<19) + startr*(1<<13) + startc*(1<<7) + 0);
	while(!Q.empty())
	{
		int raw = Q.pop();
		//if(raw / (1<<7) == 0) break;
		int curb = (raw/(1<<19))%(1<<28);
		int curr = (raw%(1<<19))/(1<<13);
		int curc = (raw%(1<<13))/(1<<7);
		/*if(curb >= (1<<9) || curr >= (1<<6) || curc >= (1<<6))
		{
			cout << "@$T%@$^$@";
			return 0;
		}*/
		int d = raw%(1<<7);
		for(int r = 0; r < 9; r++)
			for(int c = 0; c < 9; c++)
			{
				int nextb = curb, nextr = curr, nextc = curc;
				nextb ^= (1<<((r/3)*3+(c/3)));
				if(r % 3 != 2) nextr ^= (1<<(r-r/3));
				if(c % 3 != 2) nextc ^= (1<<(c-c/3));
				//cout<<nextb<<' ' <<nextr<<' '<<nextc<<endl;
				if(best[nextb][nextr][nextc] == -1)
				{
					best[nextb][nextr][nextc] = d+1;
					Q.push(nextb*(1<<19) + nextr*(1<<13) + nextc*(1<<7) + d+1);
				}
			}
	}
	cout << best[0][0][0] << endl;
	return 0;
}
