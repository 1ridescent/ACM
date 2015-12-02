#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int N, M;
int S[105];
ld prob[105][100005]; // [round][score]
ld temp[100005];

inline ld seg(int l, int r)
{
	if(l <= 0 && r < 0) return 0;
	if(l <= 0) return temp[r];
	return temp[r] - temp[l - 1];
}

int main()
{
	cin >> N >> M;
	if(M == 1)
	{
		cout << 1 << endl;
		return 0;
	}
	int score = 0;
	for(int i = 1; i <= N; i++)
	{
		cin >> S[i];
		score += S[i];
	}
	prob[0][0] = 1;
	temp[0] = prob[0][0];
	for(int s = 1; s <= 100000; s++) temp[s] = temp[s - 1] + prob[0][s];
	ld factor = 1.0 / (M - 1);
	for(int r = 1; r <= N; r++)
	{
		for(int s = 1; s <= 100000; s++)
		{
			//printf("l=%d r=%d seg=%lf\n", s - M, s - 1, seg(s - M, s - 1));
			prob[r][s] = (seg(s - M, s - 1) - seg(s - S[r], s - S[r])) * factor;
			//printf("prob[%d][%d] = %lf\n", r, s, prob[r][s]);
		}
		temp[0] = prob[r][0];
		for(int s = 1; s <= 100000; s++) temp[s] = temp[s - 1] + prob[r][s];
	}
	ld ans = 0;
	for(int s = 1; s < score; s++)
	{
		//printf("prob[N][%d] = %lf\n", s, prob[N][s]);
		ans += prob[N][s];
	}
	ans *= (M - 1);
	printf("%.12f\n", 1 + (double)ans);
}
