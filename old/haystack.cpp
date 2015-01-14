#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int delta[1000100];
int N, K;

int main()
{
	ios::sync_with_stdio(false);
	memset(delta, 0, sizeof(delta));
	cin >> N >> K;
	for(int i = 1; i <= K; i++)
	{
		int a, b;
		cin >> a >> b;
		delta[a]++;
		delta[b+1]--;
	}
	for(int i = 2; i <= N; i++)
	{
		delta[i] += delta[i-1];
	}
	sort(delta+1, delta+N+1);
	//for(int i = 1; i <= N; i++) cout << delta[i] << ' ';
	cout << delta[(N+1)/2] << endl;
	return 0;
}
