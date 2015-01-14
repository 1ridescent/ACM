#include <iostream>
#include <deque>

using namespace std;

int N;
deque<int> pile[111];
int numleft = 0;

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		int M;
		cin >> M;
		for(int j = 0; j < M; j++)
		{
			int c;
			cin >> c;
			pile[i].push_back(c);
			numleft++;
		}
	}
	int score[2] = {0, 0};
	for(int p = 0; numleft > 0; numleft--, p ^= 1)
	{
		int best = -1, besti;
		for(int i = 0; i < N; i++)
		{
			if(pile[i].size() % 2 == 1)
			{
				if(pile[i][pile[i].size()/2] > best)
				{
					best = pile[i][pile[i].size()/2];
					besti = i;
				}
			}
			if(best == -1 && !pile[i].empty()) besti = i;
		}
		if(p == 0)
		{
			score[0] += pile[besti].front();
			pile[besti].pop_front();
		}
		else
		{
			score[1] += pile[besti].back();
			pile[besti].pop_back();
		}
	}
	cout << score[0] << ' ' << score[1] << endl;
	return 0;
}
