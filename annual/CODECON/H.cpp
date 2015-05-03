#include <iostream>
#include <algorithm>

using namespace std;

int S[4];
int A[505];
int num[4][30005];

int main()
{
	cin >> S[1] >> S[2] >> S[3];
	num[0][0] = 1;
	for(int i = 1; i <= 3; i++)
	{
		for(int j = 0; j < S[i]; j++)
		{
			int x;
			cin >> x;
			for(int k = 0; k <= 30002 - x; k++)
				num[i][k + x] += num[i - 1][k];
		}
	}
	int best = -1, besti;
	for(int i = 0; i <= 30002; i++) //cout << num[3][i] << ' ';
		if(num[3][i] > best)
			best = num[3][i], besti = i;
	cout << besti << endl;
}
