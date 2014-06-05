#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int V[1010];
int total = 0;

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> V[i];
	for(int i = 1; i <= M; i++)
	{
		int a, b;
		cin >> a >> b;
		total += min(V[a], V[b]);
	}
	cout << total;
}
