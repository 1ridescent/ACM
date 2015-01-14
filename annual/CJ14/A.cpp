#include <iostream>
#include <set>
#include <cstring>

using namespace std;

int N, X;
set< pair<int, int> > S;

int main2()
{
	S.clear();
	cin >> N >> X;
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		S.insert( make_pair(x, i) );
	}
	int cnt = 0;
	while(!S.empty())
	{
		set< pair<int, int> >::iterator first = S.begin();
		int x = first->first;
		S.erase(first);
		set< pair<int, int> >::iterator next = S.upper_bound( make_pair(X - x, 1000000) );
		if(next != S.begin())
		{
			next--;
			S.erase(next);
			cnt++;
		}
		else break;
	}
	cout << N - cnt << endl;
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cout << "Case #" << t << ": ";
		main2();
	}
}
