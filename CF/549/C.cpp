#include <bits/stdc++.h>

using namespace std;

bool wins(int num0, int num1, int want, int rounds)
{
	if(num0 <= rounds) return (num1 - (2 * rounds - num0) == want);
	if(num1 <= rounds) return (0 == want);
	return false;
}
bool go(int num0, int num1, int want, int turns)
{
	if(turns % 2 == 0) return wins(num0, num1, want, turns / 2);
	else
	{
		if(num0 > 0 && !wins(num0 - 1, num1, !want, turns / 2)) return true;
		if(num1 > 0 && !wins(num0, num1 - 1, !want, turns / 2)) return true;
		return false;
	}
}

int main()
{
	int N, K, num0 = 0, num1 = 0;
	cin >> N >> K;
	for(int i = 0; i < N; i++)
	{
		int x;
		scanf("%d", &x);
		if(x % 2) num1++;
		else num0++;
	}
	//cout << num0 << ' ' << num1 << endl;
	int turns = (N - K);
	int want = 1;
	cout << (go(num0, num1, want, turns) ? "Stannis" : "Daenerys");
}
