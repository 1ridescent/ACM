#include <bits/stdc++.h>

using namespace std;

typedef complex<int> point;
#define x real()
#define y imag()

double arg2(point p)
{
	return arg(complex<double>(p.x, p.y));
}
int cross(point u, point v)
{
	return u.x * v.y - u.y * v.x;
}

int N, K;
point P[255];
int idx[555][555];

int tri[255][255][255]; // number of interior points in triangle
int span(int i, int j, int k)
{
	int r = idx[i][k] - idx[i][j] - 1;
	if(r < 0) r += (N - 1);
	return r;
}
int compute(int i, int j, int k)
{
	if(cross(P[j] - P[i], P[k] - P[i]) < 0) swap(j, k);
	return (N - 3 - span(i, k + N, j) - span(j, i + N, k) - span(k, j + N, i));
}

int main()
{
	cin>>N;//while(cin >> N >> K)
	{
		//printf("Case %d: ", ++test);
		for(int i = 0; i < N; i++)
		{
			int a, b;
			cin >> a >> b;
			P[i] = point(a, b);
		}
	}
	for(int c = 0; c < N; c++)
	{
		vector<pair<double, int> > V;
		for(int i = 0; i < N; i++)
			if(i != c)
			{
				V.push_back(make_pair(arg2(P[i] - P[c]), i));
				V.push_back(make_pair(arg2(P[c] - P[i]), i + N));
			}
		sort(V.begin(), V.end());
		int cnt = 0;
		for(int i = 0; i < V.size(); i++)
		{
			if(V[i].second < N) cnt++;
			idx[c][V[i].second] = cnt;
		}
	}
	//for(int i=0;i<2*N;i++){for(int j=0;j<2*N;j++)cout<<idx[i][j]<<' ';cout<<endl;}
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			for(int k = 0; k < N; k++)
			{
				if(i == j || j == k || k == i) continue;
				tri[i][j][k] = compute(i, j, k);
			}
	//printf("processed\n");while(true){int i,j,k;cin>>i>>j>>k;cout<<compute(i,j,k)<<endl;}

}
