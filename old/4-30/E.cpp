#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

priority_queue< pair<int, int> > low;
priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > high;
void clear()
{
	while(!low.empty()) low.pop();
	while(!high.empty()) high.pop();
}
void fix()
{
	while(low.size() < high.size())
	{
		pair<int, int> v = high.top();
		//cout << "moving " << v.first << endl;
		high.pop();
		low.push(v);
	}
	while(low.size() > high.size() + 1)
	{
		pair<int, int> v = low.top();
		//cout << "moving " << v.first << endl;
		low.pop();
		high.push(v);
	}
}
void insert(pair<int, int> v)
{
	if(low.empty() || v <= low.top()) low.push(v);
	else high.push(v);
	fix();
	//cout << low.size() << ',' << high.size() << endl;
}

int main2()
{
	int T, N;
	cin >> T >> N;
	clear();
	cout << T << ' ' << (N + 1) / 2 << '\n';
	for(int i = 1; i <= N; i++)
	{
		pair<int, int> v;
		cin >> v.first;
		v.second = i;
		insert(v);
		if(i % 2 == 1) cout << low.top().first << (i < N ? ' ' : '\n');
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--) main2();
}
