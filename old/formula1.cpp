#include <cstdio>
#include <algorithm>

using namespace std;

pair<int,int> A[1000100];
pair<int,int> A2[1000100];

inline void process(pair<int,int>& a, pair<int,int>& b) // a is before b
{
	if(a.first >= 1 && b.first >= 1)
	{
		int minus = min(a.first, b.first);
		a.first -= minus;
		b.first -= minus;
	}
	while(b.first > 0)
	{
		b.first--;
		swap(a,b);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int N;
		scanf("%d", &N);
		for(int i=0;i<N;i++)
		{
			scanf("%d", &(A[i].first));
			A[i].second = i;
			A2[i] = A[i];
		}
		for(int i=N-2;i>=0;i--) process(A[i], A[i+1]);
		if(A[0].first == 0)
		{
			printf("TAK\n");
			continue;
		}
		int bad = A[0].second;
		printf("bad=%d\n",bad);
		bool done = false;
		for(int i=bad;i<N-1;i++)
		{
			process(A2[i], A2[i+1]);
			if(A[i+1].first == 0)
			{
				printf("TAK\n");
				done = true;
				break;
			}
		}
		if(done) continue;
		for(int i=N-2;i>=0;i--)
		{
			process(A2[i], A2[i+1]);
			if(A[i].first == 0)
			{
				printf("TAK\n");
				done = true;
				break;
			}
		}
		if(done) continue;
		printf("NIE\n");
	}
	return 0;
}
