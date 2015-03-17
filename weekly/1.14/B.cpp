#include <iostream>
#include <map>

using namespace std;

int N, K;
map<int, int> delta;

void insert(int l, int r)
{
	delta[l]++;
	delta[r]--;
}

int main()
{
	cin >> N >> K;
	int pos = 0;
	for(int i = 0; i < N; i++)
	{
		int d;
		char c;
		cin >> d >> c;
		//cout << "pos = " << pos << endl;
		if(c == 'L')
		{
			insert(pos - d, pos);
			pos -= d;
		}
		else
		{
			insert(pos, pos + d);
			pos += d;
		}
	}
	int accum = 0;
	int ans = 0;
	for(map<int, int>::iterator it = delta.begin(); it != delta.end(); )
	{
		//cout << "accum = " << accum << endl;
		accum += it->second;
		if(accum >= K)
		{
			int l = it->first;
			it++;
			ans += (it->first - l);
		}
		else
			it++;
	}
	cout << ans << '\n';
}
