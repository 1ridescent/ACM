#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll N, K;
pair<ll,int> A[300300];
ll partial[300300];

int main()
{
	cin >> N;
	for(int i=1;i<=N;i++)
		{
		cin >> A[i].first;
		A[i].second = i;
		}
	cin >> K;
	sort(A+1,A+1+N);
	partial[0] = 0;
	for(int i=1;i<=N;i++) partial[i] = partial[i-1]+A[i].first;
	ll total = 0;
	for(int i=1;i<=K;i++) total += A[i].first*(2*i-(K+1));
	ll best = total;
	int besti = 1;
	//cout << 0 << ' ' << total << endl;
	for(int e=K+1;e<=N;e++)
	{
		total -= (partial[e-1]-partial[e-K])-(K-1)*A[e-K].first;
		//cout << total << endl;
		total += (K-1)*A[e].first-(partial[e-1]-partial[e-K]);
		//cout << e-K << ' ' << total << endl;
		if(total < best)
		{
			best = total;
			besti = e-K+1;
		}
	}
	for(int i=besti;i<besti+K;i++) cout << A[i].second << ' ';
	return 0;
}
