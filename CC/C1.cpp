#include <iostream>
#include <vector>
#include <map>
#include <cstdio>

using namespace std;

int N;
int list[100005][3];
int head;
int next;
void init()
{
	head = -1;
	next = 0;
}
int insert(int v, int l, int r)
{
	list[next][1] = v;
	list[next][0] = l, list[next][2] = r;
	if(l != -1) list[l][2] = next;
	else head = next;
	if(r != -1) list[r][0] = next;
	return next++;
}
void print()
{
	for(int i = head; i != -1; i = list[i][2])
		printf("%d ", list[i][1]);
	cout << endl;
}
map<int, int> M;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cin >> N;
		init();
		M.clear();
		for(int t = 0; t < N; t++)
		{
			int x;
			scanf("%d", &x);
			//printf("input %d\n", x);
			//for(map<int, int>::iterator it = M.begin(); it != M.end(); it++)
				//printf("%d ", it->first);
			//cout << endl;
			map<int, int>::iterator it = M.upper_bound(x + 1);
			if(it == M.begin())
			{
				int i = insert(x, -1, head);
				M[x] = i;
			}
			else
			{
				it--;
				int i = insert(x, it->second, list[it->second][2]);
				if(it->first == x + 1) M.erase(it);
				M[x] = i;
			}
			//print();
		}
		print();
	}
}
