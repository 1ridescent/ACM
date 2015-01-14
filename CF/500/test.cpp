#include <iostream>
using namespace std;
int main()
{
	cout << 100000 << '\n';
	for(int i = 1; i < 100000; i++) cout << i << ' ' << i + 1 << ' ' 
<< 1000 << '\n';
	cout << 100000 << '\n';
	for(int i = 1; i <= 100000; i++) cout << "1 1\n";
}
