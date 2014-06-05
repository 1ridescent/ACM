#include <iostream>

using namespace std;

int main()
{
	int A, B;
	cin >> A >> B;
	for(int x = 1; x <= 2000; x++)
		for(int y = 1; y <= 2000; y++)
		{
			if(x * x + y * y == A * A)
			{
				if((y * B) % A == 0 && (x * B) % A == 0)
				{
					if(x != y * B / A)
					{
						cout << "YES" << endl;
						cout << 0 << ' ' << 0 << endl;
						cout << x << ' ' << y << endl;
						cout << y * B / A << ' ' << -x * B / A << endl;
						return 0;
					}
				}
			}
		}
	cout << "NO\n";
}
