#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int N, K;
int X1, X0, A, B, C;
const int mask = (1<<31)-1;
#define f(x2,x1) ((A*(x2) + B*(x1) + C) & mask)

const int MAX = 1313131;
const int PIVOTS = 75757;

int T[MAX+10];

struct Pivot
{
  int i, v;
};
bool cmpi(Pivot a, Pivot b)
{
  return a.i < b.i;
}
bool cmpv(Pivot a, Pivot b)
{
  if(a.v < b.v) return true;
  if(a.v > b.v) return false;
  if(a.i < b.i) return true;
  return false;
}
Pivot pivot[PIVOTS+10];

int main()
{
  scanf("%d %d", &N, &K);
  scanf("%d %d %d %d %d", &X1, &X0, &A, &B, &C);
  if(N <= MAX)
  {
    for(int i = 1; i <= N; i++)
    {
      T[i] = f(X1, X0);
      X1 = X0;
      X0 = T[i];
    }
  }
  else
  {
    srand(time(0));
    for(int i = 0; i < PIVOTS; i++) pivot[i].i = (long long)(i) * N / PIVOTS;
    sort(pivot, pivot+PIVOTS, cmpi);
    {
      int index = 0;
      int x1 = X1, x0 = X0, x;
      for(int i = 0; i < PIVOTS; i++)
      {
        while(index < pivot[i].i)
        {
          x = f(x1, x0);
          x1 = x0;
          x0 = x;
          index++;
        }
        pivot[i].v = x;
      }
    }
    sort(pivot, pivot+PIVOTS, cmpv);
    //for(int i=0;i<1000;i++) printf("%d ",pivot[i].v);
    int pivoti = PIVOTS - 3 * (((long long)(PIVOTS)*K+N-1)/N);
    if(pivoti < 0) pivoti = 0;
    if(pivoti >= PIVOTS) pivoti = PIVOTS-1;
    //printf("v=%d i=%d\n", pivot[pivoti].v, pivot[pivoti].i);
    //return 0;
    {
      int Ti = 0;
      int x1 = X1, x0 = X0, x;
      for(int i = 1; i <= N; i++)
      {
        x = f(x1, x0);
        x1 = x0;
        x0 = x;
        if(x > pivot[pivoti].v || x == pivot[pivoti].v && i > pivot[pivoti].i)
          T[++Ti] = x;
        if(Ti == MAX) break;
      }
      N = Ti;
      //printf("Ti = %d\n", Ti);
      //return 0;
    }
  }
  //return 0;
  sort(T+1, T+1+N);
  for(int i = N; i > N-K && i >= 0; i--)
  {
    printf("%d", T[i]);
    if(i == N-K+1) printf("\n");
    else printf(" ");
  }
  return 0;
}
