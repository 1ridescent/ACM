#include <bits/stdc++.h>

using namespace std;

/***** SUFFIX ARRAY *****/

const int MAX = (1 << 21);

int n1;
char S[MAX];
int sa1[MAX];
int rank1[MAX];

int next[MAX];
int temp[MAX];
bool comp1(int a, int b)
{
  return S[a] < S[b];
}

void buildSA1()
{
  for(int i = 0; i < n1; i++)
    sa1[i] = i;
  sort(sa1, sa1 + n1, comp1);

  rank1[sa1[0]] = 0;
  for(int i = 0; i < n1-1; i++)
  {
    if(S[sa1[i]] == S[sa1[i+1]])
      rank1[sa1[i+1]] = rank1[sa1[i]];
    else
      rank1[sa1[i+1]] = i+1;
  }
  for(int len = 1; len < n1; len *= 2)
  {
    for(int i = 0; i < n1; i++)
      next[i] = i;
    for(int i = n1-len; i < n1; i++) // end have highest priority
      temp[next[rank1[i]]++] = i;
    for(int i = 0; i < n1; i++) // then, prioritize segments based on next seg
      if(sa1[i] >= len)
        temp[next[rank1[sa1[i]-len]]++] = sa1[i]-len;
    memcpy(sa1, temp, sizeof(temp)); // copy new orderings of segments into sa1
    temp[sa1[0]] = 0;
    for(int i = 0; i < n1-1; i++)
    {
      if(sa1[i] + len < n1 && sa1[i+1] + len < n1 && rank1[sa1[i]] == rank1[sa1[i+1]] && rank1[sa1[i]+len] == rank1[sa1[i+1]+len])
        temp[sa1[i+1]] = temp[sa1[i]]; // can't separate yet, so leave the same
      else
        temp[sa1[i+1]] = i+1;
    }
    memcpy(rank1, temp, sizeof(temp)); // copy new ranks into rank1
  }
}

int height[MAX];
priority_queue<pair<int, int> > Q;

int main()
{
	scanf("%s", S);
	int N = strlen(S);
	for(int i = 0; i < N; i++)
		S[N + i] = S[i];
	n1 = 2 * N;
	buildSA1();
	//for(int i = 0; i < n1; i++) printf("%d %d\n", sa1[i], rank1[i]);
	int cur = 0;
	for(int i = 0; i < N; i++)
	{
		Q.push(make_pair(-cur, i));
		cur += (S[i] == '(' ? 1 : -1);
	}
	int thr = max(cur, 0);
	int best = MAX, besti = -1;
	for(int i = 0; i < N; i++)
	{
		while(Q.top().second < i) Q.pop();
		int low = -Q.top().first;
		//printf("%d: cur = %d, low = %d\n", i,cur, low);
		if(cur <= low + thr)
		{
			//cout << i << " is good\n";
			if(rank1[i] < best)
				best = rank1[i], besti = i;
		}
		Q.push(make_pair(-cur, N + i));
		cur += (S[i] == '(' ? 1 : -1);
	}
	cur /= 2;
	while(cur < 0)
	{
		printf("(");
		cur++;
	}
	for(int i = 0; i < N; i++)
		printf("%c", S[besti + i]);
	while(cur > 0)
	{
		printf(")");
		cur--;
	}
}
