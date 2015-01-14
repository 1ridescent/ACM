#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int N, M;
int A[405][405];

int high[405], low[405];

struct deq
{
	int data[405][2];
	int f, b;
	inline void init()
	{
		f = b = 0;
	}
	inline bool empty()
	{
		return (f == b);
	}
	inline int front()
	{
		return data[f - 1][0];
	}
	inline void push_front(int v, int i)
	{
		data[f][0] = v, data[f][1] = i;
		f++;
	}
	inline void pop_front()
	{
		f--;
	}
	inline int back()
	{
		return data[b][0];
	}
	inline int back2()
	{
		return data[b][1];
	}
	inline void pop_back()
	{
		b++;
	}
};
deq high_stack, low_stack;

int main()
{
	ios::sync_with_stdio(false);
	int Q;
	cin >> N >> M >> Q;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			cin >> A[i][j];

	while(Q--)
	{
		int k;
		cin >> k;
		long long ans = 0;
		for(int l = 1; l <= N; l++)
		{
			for(int c = 1; c <= M; c++)
				high[c] = low[c] = A[l][c];
			for(int r = l; r <= N; r++)
			{
				for(int c = 1; c <= M; c++)
				{
					high[c] = max(high[c], A[r][c]);
					low[c] = min(low[c], A[r][c]);
				}
				high_stack.init();
				low_stack.init();
				int reach = 0;
				for(int c = 1; c <= M; c++)
				{
					while(!high_stack.empty() && high_stack.front() <= high[c])
						high_stack.pop_front();
					high_stack.push_front(high[c], c);
					while(!low_stack.empty() && low_stack.front() >= low[c])
						low_stack.pop_front();
					low_stack.push_front(low[c], c);
					while(!(high_stack.empty() || low_stack.empty()) && high_stack.back() - low_stack.back() > k)
					{
						int i = min(high_stack.back2(), low_stack.back2());
						reach = i;
						//cout << "reach = " << i << endl;
						if(high_stack.back2() == i)
							high_stack.pop_back();
						if(low_stack.back2() == i)
							low_stack.pop_back();
					}
					ans += (c - reach);
				}
			}
		}
		cout << ans << '\n';
	}
}
