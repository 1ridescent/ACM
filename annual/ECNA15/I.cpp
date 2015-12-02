#include <bits/stdc++.h>

using namespace std;

int N;

bool mask[123][123];
void rotate()
{
	bool mask2[123][123];
	memset(mask2, 0, sizeof(mask2));
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			mask2[j][N + 1 - i] = mask[i][j];
	memcpy(mask, mask2, sizeof(mask));
	//for(int i = 1; i <= N; i++)
	//{
	//	for(int j = 1; j <= N; j++)
	//		cout << mask[i][j];
	//	cout << endl;
	//}
}

string S;
int nexti = 0;

char ans[123][123];
void go()
{
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			if(mask[i][j])
				ans[i][j] = S[nexti++];
}


int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
		{
			char c;
			cin >> c;
			mask[i][j] = (c == '.');
		}
	cin >> S;
	for(int i = 0; i < 4; i++)
	{
		go();
		rotate();
	}
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			if(!ans[i][j])
			{
				cout << "invalid grille";
				return 0;
			}

	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			cout << ans[i][j];
}
