#include <iostream>

using namespace std;

char B[11][11];

int main()
{
	for(int i = 1; i <=8; i++)
		for(int j=1; j <= 8; j++)
		{
			cin >> B[i][j];
		}
	for(int i1 = 1; i1 <= 8; i1++)
		for(int j1 = 1; j1 <= 8; j1++)
			for(int i2 = 1; i2 <= 8; i2++)
				for(int j2 = 1; j2 <= 8; j2++)
				{
					if((i1 == i2) && (j1 == j2)) continue;
					if(B[i1][j1] == '*' && B[i2][j2] == '*')
					{
						if((i1 == i2) || (j1 == j2) || (i1 + j1 == i2 + j2) || (i1 - j1 == i2 - j2))
						{
							cout << "invalid\n";
							return 0;
						}
					}
				}
	int cnt = 0;
	for(int i = 1; i <= 8; i++)
		for(int j =1; j <= 8; j++)
		{
			cnt += (B[i][j] == '*');
		}
	if(cnt != 8) cout << "invalid\n";
	else 	cout << "valid\n";
}
