#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAX = 1<<17;
int n1;
char s[MAX];
int sa1[MAX];
int rank1[MAX];
int height1[MAX];

int next[MAX];
int temp[MAX];

bool comp1(int a, int b)
{
  return s[a] < s[b];
}

void buildSA1()
{
  for(int i = 0; i < n1; i++)
    sa1[i] = i;
  sort(sa1, sa1 + n1, comp1);
  
  rank1[sa1[0]] = 0;
  for(int i = 0; i < n1-1; i++)
  {
    if(s[sa1[i]] == s[sa1[i+1]])
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

int lcp1(int p1, int p2, int l)
{
  while(p1+l < n1 && p2+l < n1 && s[p1+l] == s[p2+l])
    l++;
  return l;
}

void calcHeight1()
{
  int pre = 0;
  for(int i = 0; i < n1; i++)
  {
    if(rank1[i] == 0)
      height1[0] = 0;
    else
    {
      pre = lcp1(sa1[rank1[i]-1], sa1[rank1[i]], max(pre-1, 0));
      height1[rank1[i]] = pre;
    }
  }
}


int seg[MAX * 2]; // segtree for height array

void seg_init()
{
  for(int i = 0; i < 2*MAX; i++)
    seg[i] = MAX;
  for(int i = 0; i < n1; i++)
    seg[MAX+i] = height1[i];
  for(int i = MAX-1; i >= 0; i--)
    seg[i] = min(seg[i*2], seg[i*2+1]);
}
int seg_lookup2(int l, int r, int p, int a, int b) // min in [l, r)
{
    //cout << l << ' ' << r << ' ' << p << ' ' << a << ' ' << b << endl;
    if(a >= r || b <= l)
        return MAX;
    if(l <= a && b <= r)
        return seg[p];
    int m = (a + b) / 2;
    return min(seg_lookup2(l, r, p * 2, a, m), seg_lookup2(l, r, p * 2 + 1, m, b));
}
int seg_lookup(int l, int r)
{
    return seg_lookup2(l, r, 1, 0, MAX);
}
int lcp(int i, int j)
{
  return seg_lookup(min(rank1[i], rank1[j])+1, max(rank1[i], rank1[j])+1);
}

int main()
{
  scanf("%d", &n1);
  scanf("%s", s);
  buildSA1();
  printf("suffix array for %s: ", s);
  for(int i = 0; i < n1; i++)
    printf("%d ", rank1[i]);
  printf("\n");
  
  calcHeight1();
  printf("height array is: ");
  for(int i = 0; i < n1; i++)
    printf("%d ", height1[i]);
  printf("\n");
  
  seg_init();
  int l, r;
  while(true)
  {
    scanf("%d %d", &l, &r);
    if(l < 0 || r < 0) break;
    printf("%d\n", lcp(l,r));
  }
  return 0;
}

