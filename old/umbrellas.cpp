#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = (1LL << 55);

int N, M;
int cows[5050];
int cost[100100];
ll best[5050];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> cows[i];
	for(int i = 1; i <= M; i++) cin >> cost[i];
	for(int i = M-1; i >= 1; i--) cost[i] = min(cost[i], cost[i+1]);
	//cout << cost[1] << endl;
	sort(cows+1, cows+N+1);
	best[0] = 0;
	for(int i = 1; i <= N; i++)
	{
		best[i] = INF;
		//best[i] = best[i-1] + cost[1];
		for(int j = 1; j <= i; j++)
		{
			//cout << "cows[i]=" << cows[i] << " cows[j]=" << cows[j] << "cost=" << cost[cows[i]-cows[j]+1] << endl;
			best[i] = min(best[i], best[j-1] + cost[cows[i] - cows[j] + 1]);
		}
	}
	cout << best[N] << endl;
	return 0;
}
