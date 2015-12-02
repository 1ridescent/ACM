#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<int> N;
ll M;
ll total = 0;

int num_unused[12]; // (PRECOMPUTED) [i] = # digits unused in N[1..i-1] that are < N[i]

ll dpLess[12], dpEqual[12];
ll process(int* F, int len, int nxt)
{
	ll val = 0;
	for(int i = 0; i < len; i++)
	{
		val *= 10;
		val += (F[i]<2?(1^F[i]):F[i]);
		val %= M;
	}
	if(len < N.size())
	{
		ll ways = 1;
		for(int i = 0; i < nxt; i++)
			ways *= min(9, 10 - i);
		return ways * val;
	}
	memset(dpLess, 0, sizeof(dpLess));
	memset(dpEqual, 0, sizeof(dpEqual));
	dpEqual[0]=1;
	int maxf = -1;
	bool used[15]; // is this digit used?
	int firstF[15]; // firstF[i] = smallest j such that F[j] = i
	memset(used, 0, sizeof(used));
	memset(firstF, -1, sizeof(firstF));
	for(int i = 0; i < len; i++)
	{
		maxf = max(maxf, F[i]);
		if (firstF[F[i]] == -1)
		{
			firstF[F[i]] = i;
			dpLess[i+1] = dpLess[i]*(10-F[i]);
			if(dpEqual[i])
			{
				if(!used[N[i]])
					dpEqual[i+1]++;
				dpLess[i+1] += num_unused[i];
				if(i==0&&!used[0])dpLess[i+1]--;
			}
		}
		else
		{
			dpLess[i+1] = dpLess[i];
			if(dpEqual[i])
			{
				int newdigit = N[firstF[F[i]]];
				if (newdigit < N[i])
  dpLess[i+1]++;
else if (newdigit == N[i])
  dpEqual[i+1]++;
			}
		}
		used[N[i]] = true;
	}
//	for(int i=0;i<len;i++)cout<<F[i];	cout<<": val="<<val<<" dpEqual="<<dpEqual[len]<<" Less="<<dpLess[len]<<endl;
	return val * (dpEqual[len]+dpLess[len]);
}

int S[12];
void generate(int i, int nxt, int lft)
{
	if(lft == 0)
	{
		total += process(S, i, nxt);
		return;
	}
	for(int c = 0; c < nxt; c++)
	{
		S[i] = c;
		generate(i + 1, nxt, lft - 1);
	}
	S[i] = nxt;
	generate(i + 1, nxt + 1, lft - 1);
}

int main2()
{
	total=0;
	string SN;
	cin >> SN >> M;
	if(SN == "100000000000")
	{
		total += 100000000000LL % M;
		SN = "99999999999";
	}
	N.clear();
	for(int i = 0; i < SN.size(); i++)
		N.push_back((int)(SN[i] - '0'));
	//cout <<"N len=" << N.size()<<endl;

	bool used[12];
	memset(used, 0, sizeof(used));
	memset(num_unused,0,sizeof(num_unused));
	for(int i = 0; i < N.size(); i++)
	{
		for(int d = 0; d < N[i]; d++)
			if(!used[d])
				num_unused[i]++;
		used[N[i]] = true;
	}

	for(int l = 1; l <= N.size(); l++)
		generate(0, 0, l);
	cout<<total<<endl;
}


int main()
{
	int T;cin >>T;while(T--)main2();
}
