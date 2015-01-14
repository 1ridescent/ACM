#include <iostream>

using namespace std;

int color[100100][4];
int freq[100100];

int main()
{
	ios::sync_with_stdio(false);
	int N;
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> color[i][1] >> color[i][2];
		freq[color[i][1]]++;
	}
	for(int i = 1; i <= N; i++)
	{
		cout << N - 1 + freq[color[i][2]] << ' ' << N - 1 - freq[color[i][2]] << '\n';
	}
}
