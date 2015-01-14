#include <iostream>
#include <cstring>

using namespace std;

int num[6][6];
bool good[6][6];
int seq[77];

bool check()
{
	for(int i = 1; i <= 5; i++)
	{
		bool b = true;
		for(int j = 1; j <= 5; j++)
		{
			if(!good[i][j]) b = false;
		}
		if(b) return true;
	}
	for(int j = 1; j <= 5; j++)
	{
		bool b = true;
		for(int i = 1; i <= 5; i++)
		{
			if(!good[i][j]) b = false;
		}
		if(b) return true;
	}
	{
		bool b = true;
		for(int i = 1; i <= 5; i++)
			if(!good[i][i]) b = false;
		if(b) return true;
	}
	{
		bool b = true;
		for(int i = 1; i <= 5; i++)
			if(!good[i][6 - i]) b = false;
		if(b) return true;
	}
	return false;
}

int main()
{
int T;cin>>T;while(T--){

	for(int i = 1; i <= 5; i++)
		for(int j = 1; j <= 5; j++)
		{
			if(i == 3 && j == 3)
			{
				num[i][j] = 0;
				continue;
			}
			cin >> num[i][j];
		}

	memset(good, 0, sizeof(good));
	good[3][3] = true;

	for(int i = 1; i <= 75; i++) cin >> seq[i];

	for(int t = 1; t <= 75; t++)
	{
		int x = seq[t];
		for(int i = 1; i <= 5; i++)
			for(int j = 1; j <= 5; j++)
				if(num[i][j] == x)
					good[i][j] = true;
		if(check())
		{
			cout << "BINGO after " << t << " numbers announced\n";
			break;
		}
	}
}}
