#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

ll num[35][8];

void setup()
{
	memset(num, 0, sizeof(num));

	num[0][7] = 1;
	for(int i = 1; i <= 32; i++)
	{
		num[i][1] += num[i - 1][6];
		num[i][2] += num[i - 1][5];
		num[i][4] += num[i - 1][3];
		num[i][3] += num[i - 1][7] + num[i - 1][4];
		num[i][5] += num[i - 1][2];
		num[i][6] += num[i - 1][7] + num[i - 1][1];
		num[i][7] += num[i - 1][3] + num[i - 1][6];
		if(i > 1) num[i][7] += num[i - 2][7];
	}

	return;
	for(int i = 1; i <= 30; i++)
	{
		for(int j = 1; j <= 7; j++) cout << num[i][j] << ' ';
		cout << endl;
	}
}

int main()
{
	setup();
	while(true)
	{
		int x;
		cin >> x;
		if(x == -1) return 0;
		cout << num[x][7] << '\n';
	}
}
