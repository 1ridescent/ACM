#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int ans[205];

int loc[10][2];

void setup()
{
	loc[1][0] = 1, loc[1][1] = 1;
	loc[2][0] = 1, loc[2][1] = 2;
	loc[3][0] = 1, loc[3][1] = 3;
	loc[4][0] = 2, loc[4][1] = 1;
	loc[5][0] = 2, loc[5][1] = 2;
	loc[6][0] = 2, loc[6][1] = 3;
	loc[7][0] = 3, loc[7][1] = 1;
	loc[8][0] = 3, loc[8][1] = 2;
	loc[9][0] = 3, loc[9][1] = 3;
	loc[0][0] = 4, loc[0][1] = 2;
	/*loc[1] = {1, 1};
	loc[2] = {1, 2};
	loc[3] = {1, 3};
	loc[4] = {2, 1};
	loc[5] = {2, 2};
	loc[6] = {2, 3};
	loc[7] = {3, 1};
	loc[8] = {3, 2};
	loc[9] = {3, 3};
	loc[0] = {4, 2};*/
}

bool to(int a, int b)
{
	return (loc[a][0] <= loc[b][0] && loc[a][1] <= loc[b][1]);
}

bool Try(int x)
{
	deque<int> V;
	while(x > 0)
	{
		V.push_front(x % 10);
		x /= 10;
	}
	for(int i = 1; i < V.size(); i++)
	{
		if(!to(V[i - 1], V[i])) return false;
	}
	return true;
}

void solve()
{
	for(int i = 0; i <= 200; i++)
	{
		ans[i] = 0;
		for(int k = 0; k <= 200; k++)
		{
			if(Try(k) && abs(k - i) < abs(ans[i] - i))
				ans[i] = k;
		}
	}
}

int main()
{
	setup();
	solve();
	int T;
	cin >> T;
	while(T--)
	{
		int x;
		cin >> x;
		cout << ans[x] << '\n';
	}
}
