#include <iostream>

using namespace std;

int main()
{
	int N;
	cin >> N;
	if(N <= 3)
	{
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n";
	int s;
	if(N % 2 == 0)
	{
		cout << "1 * 2 = 2\n2 * 3 = 6\n6 * 4 = 24\n";
		s = 5;
	}
	else
	{
		cout << "3 * 5 = 15\n2 * 4 = 8\n15 + 8 = 23\n23 + 1 = 24\n";
		s = 6;
	}
	for(; s <= N; s += 2)
		cout << s + 1 << " - " << s << " = 1\n24 * 1 = 24\n";
}
