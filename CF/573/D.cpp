#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
int new_index[30005];

ll power[30005];
ll horse_power[30005];
int horse_rank[30005];

ll input1[30005];
ll input2[30005];
pair<ll, pair<ll, int> > input3[30005];
pair<ll, int> input4[30005];

#define NUM_SEGS 155
#define SEG_SIZE 200

ll seg_dp[NUM_SEGS][3][3];

void compute_seg_dp(int seg)
{
	ll dp2[SEG_SIZE + 3];
	ll* dp = dp2 + 1;
	for(int s = 0; s <= 2; s++)
	{
		memset(dp2, -1, sizeof(dp2));
		dp[s - 1] = 0;
		for(int j = s; j <= SEG_SIZE + 2; j++)
		{
			int i = seg * SEG_SIZE + j;
			if(i != horse_rank[i])
			{
				if(dp[i - 1] >= 0) dp[i] = dp[i - 1] + power[i] * horse_power[i];
			}
			else if(j >= 2 && i == horse_rank[i] && i - 1 == horse_rank[i - 1])
			{
				if(dp[i - 2] >= 0) dp[i] = max(dp[i], dp[i - 2] + power[i] * horse_power[i - 1] + power[i - 1] * horse_power[i]);
			}
			else if(j >= 3 && i == horse_rank[i] && i - 1 == horse_rank[i - 1] && i - 2 == horse_rank[i - 2])
			{
				if(dp[i - 3] >= 0) dp[i] = max(dp[i], max(
						power[i]*horse_power[i-1] + power[i-1]*horse_power[i-2] + power[i-2]*horse_power[i],
						power[i-1]*horse_power[i] + power[i-2]*horse_power[i-1] + power[i]*horse_power[i-2]) );
			}
		}
		for(int t = 0; t <= 2; t++)
			seg_dp[seg][s][t] = dp[SEG_SIZE + t];
	}
}

ll compute_overall()
{
	ll dp[NUM_SEGS][3];
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	for(int i = 0; i < NUM_SEGS; i++)
	{
		for(int s = 0; s <= 2; s++)
			for(int t = 0; t <= 2; t++)
				if(seg_dp[i][s][t] >= 0)
					dp[i + 1][t] = max(dp[i + 1][t], dp[i][s] + seg_dp[i][s][t]);
	}
	return dp[NUM_SEGS][0];
}

int main()
{
	int Q;
	cin >> N >> Q;
	for(int i = 1; i <= N; i++) cin >> input1[i];
	for(int i = 1; i <= N; i++) cin >> input2[i];
	for(int i = 1; i <= N; i++)
		input3[i] = make_pair(input1[i], make_pair(input2[i], i));
	sort(input3 + 1, input3 + 1 + N);
	for(int i = 1; i <= N; i++)
	{
		power[i] = input3[i].first;
		horse_power[i] = input3[i].second.first;
		new_index[input3[i].second.second] = i;
	}
	for(int i = 1; i <= N; i++) input4[i] = make_pair(horse_power[i], i);
	sort(input4 + 1, input4 + 1 + N);
	for(int i = 1; i <= N; i++) horse_rank[input4[i].second] = i;

	for(int i = 0; i < NUM_SEGS; i++) compute_seg_dp(i);

	while(Q--)
	{
		int a, b;
		cin >> a >> b;
		a = new_index[a], b = new_index[b];
		swap(horse_rank[a], horse_rank[b]);
		swap(horse_power[a], horse_power[b]);
		int i = (a - 1) / SEG_SIZE;
		int j = (b - 1) / SEG_SIZE;
		compute_seg_dp(i);
		if(i > 0) compute_seg_dp(i - 1);
		compute_seg_dp(j);
		if(j > 0) compute_seg_dp(j - 1);
		cout << compute_overall () << '\n';
	}
}
