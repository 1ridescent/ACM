#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

int main2()
{
	int N;
	cin >> N;
	list<int> L;
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		L.push_back(x);
	}
	int total = 0;
	while(!L.empty())
	{
		int minv = 1231231231, mini;
		list<int>::iterator minit;
		int i = 0;
		for(list<int>::iterator it = L.begin(); it != L.end(); it++, i++)
		{
			if(*it < minv) minv = *it, minit = it, mini = i;
		}
		total += min(mini, (int)L.size() - 1 - mini);
		L.erase(minit);
	}
	cout << total << endl;
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
