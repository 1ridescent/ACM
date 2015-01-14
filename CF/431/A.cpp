#include <iostream>

using namespace std;

long long A[5];

int main()
{
	cin >> A[1] >> A[2] >> A[3] >> A[4];
	string S;
	cin >> S;
	long long total = 0;
	for(int i = 0; i < S.size(); i++) total += A[S[i] - '0'];
	cout << total;
}
