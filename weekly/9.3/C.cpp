#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int row[7], col[7], d1, d2;
int num[77];
int loc[75][2];

int main()
{
	ios::sync_with_stdio(false);
int T;cin>>T;while(T--){

	memset(row, 0, sizeof(row));
	memset(col, 0, sizeof(col));

	row[3] = col[3] = 1;
	d1 = d2 = 1;

	memset(loc, 0, sizeof(loc));
	for(int r = 1; r <= 5; r++)
		for(int c = 1; c <= 5; c++)
		{
			if(r == 3 && c == 3) continue;
			int x;
			cin >> x;
			loc[x][0] = r, loc[x][1] = c;
		}

	for(int i = 1; i <= 75; i++) cin >> num[i];

	int val = -1;
	for(int i = 1; i <= 75; i++)
	{
		int x = num[i];
		if(loc[x][0] != 0)
		{
			int r = loc[x][0], c = loc[x][1];
			row[r]++;
			col[c]++;
			if(r == c) d1++;
			if(r + c == 6) d2++;
			if(row[r] == 5 || col[c] == 5 || d1 == 5 || d2 == 5)
			{
				cout << "BINGO after " <<i<< " numbers announced\n";
				break;
			}
			//cout << i << ": " << row[r] << ' ' << col[c] << endl;
		}
	}
	// << "BINGO after " << val << " num"
}}
