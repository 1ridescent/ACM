#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)

#define EPS 1e-10
#define PI 3.141592653589793238462

/* pnt denotes complex numbers: x=real part, y=imaginary part */
typedef struct struct_point{double x,y;}pnt;

pnt pntPlus(pnt a,pnt b){a.x+=b.x; a.y+=b.y; return a;}
pnt pntMinus(pnt a,pnt b){a.x-=b.x; a.y-=b.y; return a;}
pnt pntMultiple(pnt a,pnt b){pnt c; c.x=a.x*b.x-a.y*b.y; c.y=a.x*b.y+a.y*b.x; return c;}
pnt pntMultipleDouble(pnt a,double k){a.x*=k; a.y*=k; return a;}

pnt pntPolar(double r,double t){pnt a; a.x=r*cos(t); a.y=r*sin(t); return a;} /* r * exp(i*t), i=sqrt(-1) */
pnt pntGenerator(double x,double y){pnt res; res.x=x; res.y=y; return res;}   /* x + i*y */

/* Fast Fourier Transform */
/* n = size of a = a power of 2, theta = 2*PI/n */
/* for inverse fft, theta = -2*PI/n */
void fft(int n, double theta, pnt a[]){
  int i, j, k, m, mh;
  pnt w, x;

  for(m=n; m>=2; m/=2){
    mh = m / 2;
    rep(i,mh){
      w = pntPolar(1, i*theta);
      for(j=i; j<n; j+=m){
        k = j+mh;
        x = pntMinus(a[j], a[k]);
        a[j] = pntPlus(a[j], a[k]);
        a[k] = pntMultiple(w, x);
      }
    }
    theta *= 2;
  }

  i = 0;
  REP(j,1,n-1){
    for(k=n/2; k > (i ^= k); k/=2);
    if(j < i) w=a[i], a[i]=a[j], a[j]=w;
  }
}

const int N2 = 65536;
const int M = 30000;
const double invN2 = 1.0 / 65536;
pnt p1[N2], p2[N2];

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

#define VALID(x) (0 <= (x) && (x) <= 30010)
ll freq[30030];
ll slow(vector<int> V)
{
	memset(freq, 0, sizeof(freq));
	ll res = 0;
	for(int m = 0; m < V.size(); m++)
	{
		for(int r = m + 1; r < V.size(); r++)
		{
			int target = 2 * V[m] - V[r];
			if(VALID(target)) res += freq[target];
		}
		freq[V[m]]++;
	}
	return res;
}

#define SEG 2500
ll solve(vector<int> V)
{
	ll res = 0;
	vector<vector<int> > S;

	/* 3 */
	for(int i = 0; i < V.size(); i += SEG)
	{
		S.push_back(vector<int>());
		for(int j = i; j < V.size() && j < i + SEG; j++) S.back().push_back(V[j]);
		res += slow(S.back());
	}

	/* 2 + 1 */
	memset(freq, 0, sizeof(freq));
	for(int s = 0; s < S.size(); s++)
	{
		for(int m = 0; m < S[s].size(); m++)
			for(int r = m + 1; r < S[s].size(); r++)
			{
				int target = 2 * S[s][m] - S[s][r];
				if(VALID(target)) res += freq[target];
			}
		for(int i = 0; i < S[s].size(); i++) freq[S[s][i]]++;
	}
	memset(freq, 0, sizeof(freq));
	for(int s = S.size() - 1; s >= 0; s--)
	{
		for(int l = 0; l < S[s].size(); l++)
			for(int m = l + 1; m < S[s].size(); m++)
			{
				int target = 2 * S[s][m] - S[s][l];
				if(VALID(target)) res += freq[target];
			}
		for(int i = 0; i < S[s].size(); i++) freq[S[s][i]]++;
	}

	/* 1 + 1 + 1 */
	for(int m = 1; m < S.size() - 1; m++)
	{
		vector<ll> bef(32768, 0);
		for(int l = 0; l < m; l++)
			for(int i = 0; i < S[l].size(); i++)
				bef[S[l][i]]++;
		vector<ll> aft(32768, 0);
		for(int r = m + 1; r < S.size(); r++)
			for(int i = 0; i < S[r].size(); i++)
				aft[S[r][i]]++;
		vector<ll> inside(32768, 0);
		for(int i = 0; i < S[m].size(); i++)
			inside[S[m][i]]++;

		int i, j;
	      rep(i,N2) p1[i] = p2[i] = pntGenerator(0, 0);
	      rep(i,M) p1[i].x = bef[i], p2[i].x = aft[i];

	      fft(N2, 2*PI*invN2, p1);
	      fft(N2, 2*PI*invN2, p2);
	      rep(i,N2) p1[i] = pntMultiple(p1[i], p2[i]);
	      fft(N2,-2*PI*invN2, p1);
	      rep(i,N2) p1[i].x *= invN2;

	      rep(i,M) res += inside[i] * (ll)( p1[2*i].x + 0.5 );

	}

	return res;
}

int main()
{
	int N;
	cin >> N;
	vector<int> A(N);
	for(int i = 0; i < N; i++) cin >> A[i];
	cout << solve(A) << '\n';
}
