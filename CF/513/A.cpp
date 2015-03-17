#include <iostream>

using namespace std;

int N[2], K[2];
int W[55];

int main()
{
	cin >> N[0] >> N[1] >> K[0] >> K[1];
	if(N[0] > N[1]) cout << "First\n";
	else cout << "Second\n";
}
