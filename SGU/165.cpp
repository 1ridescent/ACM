#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

typedef long long ll;

int N;
deque< pair<ll, int> > A;

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		double x;
		cin >> x;
		A.push_back(make_pair((ll)(x * 1000000.0 + 0.5) - 2000000, i));
	}
	sort(A.begin(), A.end());
	cout << "yes\n";
	ll sum = 0;
	for(int i = 1; i <= N; i++)
	{
		if(sum >= 0)
		{
			cout << A.front().second << ' ';
			sum += A.front().first;
			A.pop_front();
		}
		else
		{
			cout << A.back().second << ' ';
			sum += A.back().first;
			A.pop_back();
		}
	}
}
