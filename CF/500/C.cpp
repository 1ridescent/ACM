#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, M;
int W[505];
vector<int> cur;

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> W[i];
	long long ans = 0;
	while(M--)
	{
		int x;
		cin >> x;
		bool found = false;
		for(int i = 0; i < cur.size(); i++)
		{
			if(cur[i] == x)
			{
				for(int j = i + 1; j < cur.size(); j++)
					ans += cur[j];
				cur.erase(cur.begin() + i);
				cur.push_back(x);
				found = true;
				break;
			}
		}
		if(!found)
		{
			for(int i = 0; i < cur.size(); i++)
				ans += cur[i];
			cur.push_back(x);
		}
	}
	cout << ans;
}
