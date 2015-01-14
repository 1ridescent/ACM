// Author: Lech Duraj

#include <cstdio>
#include <algorithm>

using namespace std;

typedef pair<int,int> PI;

const int maxn = 150000;
const int maxk = 9;

const int infty = 2e9;

PI A[maxn];
int B[maxk+1][maxn+1];


int main()
{
  int TT;
  scanf("%d",&TT);
  while(TT--)
  {
    int n,k;
    scanf("%d %d",&n,&k);
    for(int i=0; i<n; i++)
      scanf("%d %d",&A[i].first,&A[i].second);
    sort(A,A+n);
    B[0][n] = -infty;
    for(int i=n-1; i>=0; i--)
      B[0][i] = max(B[0][i+1],A[i].first-A[i].second);
    for(int q=1; q<=k; q++)
    {
      B[q][n] = -infty;
      for(int i=n-1; i>=0; i--)
      {
        int u = min(A[i].first-A[i].second,B[q-1][i+1]-A[i].second);
        B[q][i] = max(u,B[q][i+1]);
        if (i+q>n)
          B[q][i] = -infty;
      }
    }
    printf("%d\n",max(B[k][0],0));
  }
}
