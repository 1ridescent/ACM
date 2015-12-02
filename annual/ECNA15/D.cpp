#include <bits/stdc++.h>

using namespace std;

int N, M;
char B[105][105];
int ans[105][105];
int temp[105][105];

int main()
{
//	memset(ans, 63, sizeof(ans))
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		for(int j =1; j <= M; j++)
		{
			cin >> B[i][j];
			if(B[i][j] != '.') ans[i][j] = 123220;
		}
	for(int k = 0; k <= 1000; k++)
	{
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= M; j++)
				temp[i][j] = min(ans[i][j], 1+ min( min( ans[i][j+1] , ans[i][j-1] ) , min( ans[i-1][j] , ans[i+1][j] ) ));
		for(int i =1 ;i  <= N; i++)
			for(int j = 1; j <= M; j++)
				ans[i][j] = temp[i][j];
	}
	bool three = false;
	for(int i =1; i <= N; i++)for(int j = 1; j <= M; j++) if(ans[i][j] >= 10) three  = true;
	for(int i = 1; i <= N; i++)
	{
		for(int j =1; j <= M; j++)
		{
			if(three) cout << '.';
			if(ans[i][j] < 10) cout << '.';
			if(ans[i][j] == 0) cout << '.';
			else cout << ans[i][j];
			//assert(ans[i][j] < 100);
		}
		cout << endl;
	}

}
