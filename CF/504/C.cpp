#include <iostream>
#include <set>

using namespace std;

int N;
int A[100005];

int cnt[100005];
int freq[3];

int R[100005];

int l = 1, r = 1;

inline int cat(int f)
{
	if(f < 0) return 2;
	return f % 2;
}
void incr(int i)
{
	//cout << "increasing... prev = " << cat(cnt[i]) << endl;
	freq[cat(cnt[i])]--;
	cnt[i]++;
	//cout << "increasing... next = " << cat(cnt[i]) << endl;
	freq[cat(cnt[i])]++;
}
void decr(int i)
{
	freq[cat(cnt[i])]--;
	cnt[i]--;
	freq[cat(cnt[i])]++;
}
void print()
{
	//cout << "l=" << l << " r=" << r << " 0=" << freq[0] << " 1=" << freq[1] << " 2=" << freq[2] << endl;
}
bool valid()
{
	bool res;
	if(N % 2 == 1 && l <= N / 2 + 1 && N / 2 + 1 <= r)
		res = (freq[2] == 0 && freq[1] == 1);
	else
		res = (freq[2] == 0 && freq[1] == 0);
	//cout << l << ' ' << r << " : " << res << endl;
	return res;
}

void add_r()
{
	//cout << "prev: "; print();
	//cout << "l = " << l << "; adding " << r << endl;
	if(r <= N / 2) // left
	{
		incr(A[r]);
		decr(A[N + 1 - r]);
	}
	else if(r >= N + 1 - N / 2) // right
	{
		incr(A[r]);
		if(l >= N + 1 - r) decr(A[N + 1 - r]);
		else
			incr(A[r]);
	}
	else // mid
	{
		incr(A[r]);
	}
	//cout << "next: "; print();
}
void extend()
{
	if(r > N) return;
	print();
	while(!valid())
	{
		r++;
		print();
		if(r > N) return;
		add_r();
	}
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i];
	int r0 = -1;
	for(int i = 1; i <= N / 2; i++)
	{
		if(A[i] != A[N + 1 - i]) r0 = i;
	}
	if(r0 == -1)
	{
		long long ans = N;
		cout << (ans * (ans + 1)) / 2 << endl;
		return 0;
	}
	//cout << "r0 = " << r0 << endl;
	r = 0;
	while(true)
	{
		r++;
		//cout << "r = " << r << endl;
		add_r();
		//print();
		if(r >= r0) break;
	}
	extend();
	R[l] = r;
	while(l <= N)
	{
		if(r > N) break;
		//cout << "incrementing l..."; print();
		if(l <= N / 2)
		{
			//cout << "removing " << l << endl;
			decr(A[l]);
			if(r < N + 1 - l)
			{
				//cout << 1 << endl;
				incr(A[N + 1 - l]);
			}
			else
			{
				//cout << 2 << endl;
				decr(A[l]);
			}
			print();
			if(A[l] != A[N + 1 - l])
			{
				while(r < N + 1 - l)
				{
					r++;
					add_r();
				}
				//cout << "r is now " << r << endl;
			}
		}
		else if(l >= N + 1 - N / 2)
		{
			decr(A[l]);
			incr(A[N + 1 - l]);
			if(A[l] != A[N + 1 - l]) break;
		}
		else
		{
			decr(A[l]);
		}
		l++;
		extend();
		if(r > N) break;
		R[l] = r;
	}
	//for(int i = 1; i <= N; i++)	cout << R[i] << ' '; cout << endl;
	long long ans = 0;
	for(int i = 1; i <= N; i++)
	{
		if(1 <= R[i] && R[i] <= N)
			ans += R[i] - l + 1;
	}
	cout << ans << endl;
}
