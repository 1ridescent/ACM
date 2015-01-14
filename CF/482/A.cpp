#include <iostream>
#include <deque>

using namespace std;

deque<int> V;

int main()
{
	ios::sync_with_stdio(false);

	int N, K;
	cin >> N >> K;

	for(int i = 1; i <= N; i++) V.push_back(i);

	for(int i = K + 1; i < N; i++)
	{
		cout << V.front() << ' ';
		V.pop_front();
	}
	while(true)
	{
		if(V.empty()) return 0;
		cout << V.front() << ' ';
		V.pop_front();
		if(V.empty()) return 0;
		cout << V.back() << ' ';
		V.pop_back();
	}
}
