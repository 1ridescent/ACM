#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int N;
int S[100005], R[100005];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> S[i] >> R[i];
	int cur_r = 2e9;
	int ans = 0;
	for(int i = N; i >= 1; i--)
	{
		int s = S[i], r = R[i];
		if(r <= cur_r) ans++;
		cur_r = min(cur_r, r);
	}
	cout << ans << endl;
}
