#include <iostream>
#include <cstdlib>

using namespace std;

int N;
int A[200200];
bool poss[200200][7]; // [i]: i days left in reading last recorded book
pair<int,int> from[200200][7];
int B[200200];

void impossible()
{
	cout << -1 << endl;
	exit(0);
}
bool valid(int books, int days)
{
	return (2*days <= books && books <= 5*days);
}
void fill(int l, int r, int b1, int b2) // start b1 at l, start b2 at r
{
	if(b1 == b2) return;
	cout << l << ' '<< r << ' '<< b1 << ' '<< b2 << endl;
	int div = (r-l)/(b2-b1), mod = (r-l)%(b2-b1);
	for(int i = 0; i < mod; i++)
	{
		for(int j = 0; j < div+1; j++) A[l++] = b1;
		b1++;
	}
	for(int i = 0; i < (b2-b1)-mod; i++)
	{
		for(int j = 0; j < div; j++) A[l++] = b1;
		b1++;
	}
}

int main()
{
	cin >> N;
	for(int i=1;i<=N;i++) cin >> A[i];

	A[0] = 0;
	int last = 0;
	poss[0][0] = true;
	for(int i=1;i<=4;i++) poss[0][i] = false;
	for(int i = 1; i <= N; i++)
	{
		if(A[i] == 0) continue;
		if(A[i] == A[last])
		{
			for(int d = 0; d < 5; d++)
			{
				if(d-(i-last) >= 0 && poss[last][d-(i-last)])
				{
					poss[i][d] = true;
					from[i][d] = make_pair(last,d-(i-last));
				}
				else poss[i][d] = false;
			}
			continue;
		}
		for(int d = 0; d <= 4; d++) // d days left in reading this book
		{
			poss[i][d] = false;
			for(int d2 = max(1, 2-d); d2 <= 5-d; d2++) // d2 days in reading this book
			{
				if(valid((i-d2) - (last+d), A[i]-A[last]-1))
				{
					poss[i][d] = true;
					from[i][d] = make_pair(last, d2);
					break;
				}
			}
		}
		/*poss[last][0] = (day[2] || day[3] || day[4] || day[5]);
		poss[last][1] = (day[1] || day[2] || day[3] || day[4]);
		poss[last][2] = (day[1] || day[2] || day[3]);
		poss[last][3] = (day[1] || day[2]);
		poss[last][4] = day[1];*/
		last = i;
	}

	cout << last << endl;

	pair<int,int> cur;
	cur.first = last;
	// fill in remaining
	if(last == N) // edge case 0
	{
		if(!poss[last][0]) impossible();
		cur.second = 0;
	}
	else if(last == N-1) // edge case 1
	{
		if(!poss[last][1]) impossible();
		A[N] = A[last];
		cur.second = 1;
	}
	else
	{
		int min_left = 11; // min days left
		for(int i=4; i>=0; i--) if(poss[last][i]) min_left = i;
		if(min_left == 11) impossible();
		for(int i=1; i<=min_left; i++) A[last+i] = A[last];
		for(int next = A[last]+1, i = last+min_left+2; i <= N; next++, i += 2)
		{
			A[i] = A[i-1] = next;
		}
		if(A[N] == 0) A[N] = A[N-1];
		cur.second = min_left;
	}

	cout << "Asdfsf " << endl;

	while(cur.first != 0)
	{
		cout << cur.first << ' ' << cur.second<< endl;
		pair<int,int> prev = from[cur.first][cur.second];
		cout << prev.first << ' ' << prev.second << endl;
		if(A[prev.first] == A[cur.first]) // same book
		{
			cout << "same book" << endl;
			for(int i = prev.first+1; i <= cur.first-1; i++) A[i] = A[prev.first];
		}
		else
		{
			cout << "filling " << endl;
			int l = prev.first + prev.second + 1, r = cur.first - max(0, 2-cur.second);
			int b1 = A[prev.first]+1, b2 = A[cur.first];
			fill(l,r,b1,b2);
		}
		cur = prev;
	}

	cout << A[N] << endl;
	for(int i=1;i<=N;i++) cout << A[i] << ' ';
	cout << endl;

	return 0;
}
