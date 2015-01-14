#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int R, C;
char W[2020][2020];

#define UP(i,k) for(int i=0;i<k;i++)
#define DOWN(i,k) for(int i=k-1;i>=0;i--)

bool test()
{
	UP(i,R) UP(j,C) if(W[i][j] == 'w') return false;
	return true;
}
void impossible()
{
	printf("-1\n");
	exit(0);
}
void print()
{
	if(test())
	{
		UP(i,R)
		{
			UP(j,C)
			{
				if(W[i][j] == '.') cout << '.';
				else if(W[i][j] <= '.'+13) cout << '+';
				else cout << 'w';
			}
			cout << endl;
		}
		exit(0);
	}
	else impossible();
}
void get_boundary(int& r0, int& r1, int& c0, int& c1)
{
	r0 = r1 = c0 = c1 = -1;
	UP(i,R) UP(j,C) if(W[i][j] == 'w') r1 = i;
	DOWN(i,R) UP(j,C) if(W[i][j] == 'w') r0 = i;
	UP(j,C) UP(i,R) if(W[i][j] == 'w') c1 = j;
	DOWN(j,C) UP(i,R) if(W[i][j] == 'w') c0 = j;
}
bool contains(int r0, int r1, int c0, int c1)
{
	for(int i=r0;i<=r1;i++) for(int j=c0;j<=c1;j++) if(W[i][j] == 'w') return true;
	return false;
}
void set(int r0, int r1, int c0, int c1)
{
	for(int i=r0;i<=r1;i++) for(int j=c0;j<=c1;j++) W[i][j]++;
}

int main()
{
	cin >> R >> C;
	for(int i=0;i<R;i++) scanf("%s",W[i]);
	int r0, r1, c0, c1;
	get_boundary(r0,r1,c0,c1);
	if(r1-r0 == c1-c0) // definite
	{
		set(r0,r1,c0,c0);
		set(r0,r1,c1,c1);
		set(r0,r0,c0,c1);
		set(r1,r1,c0,c1);
		print();
	}
	else
	{
		if(r1-r0 > c1-c0) // expand col width
		{
			int r = r1-r0+1;
			if(C < r) impossible();
			set(r0,r0,c0,c1);
			set(r1,r1,c0,c1);
			int oldc0 = c0, oldc1 = c1;
			int junk;
			get_boundary(junk,junk,c0,c1);
			if(c0 == -1)
			{
				if(oldc1 - (r-1) < 0)
				{
					set(r0,r1,0,0);
					set(r0,r1,r-1,r-1);
					set(r0,r0,0,r-1);
					set(r1,r1,0,r-1);
				}
				else
				{
					set(r0,r1,oldc1-(r-1),oldc1-(r-1));
					set(r0,r1,oldc1,oldc1);
					set(r0,r0,oldc1-(r-1),oldc1);
					set(r1,r1,oldc1-(r-1),oldc1);
				}
				print();
			}
			//else if(oldc0 < c0 || c1 < oldc1) impossible();
			else if(c0 == c1)
			{
				if(c0 - (r-1) >= 0)
				{
					set(r0,r1,c0-(r-1),c0-(r-1));
					set(r0,r1,c0,c0);
					set(r0,r0,c0-(r-1),c0);
					set(r1,r1,c0-(r-1),c0);
					print();
				}
				else if(c0 + (r-1) < C)
				{
					set(r0,r1,c0,c0);
					set(r0,r1,c0+(r-1),c0+(r-1));
					set(r0,r0,c0,c0+(r-1));
					set(r1,r1,c0,c0+(r-1));
					print();
				}
				else impossible();
			}
			else impossible();
		}
		else // expand row width
		{
			int c = c1-c0+1;
			if(c > R) impossible();
			set(r0,r1,c0,c0);
			set(r0,r1,c1,c1);
			int oldr0 = r0, oldr1 = r1;
			int junk;
			get_boundary(r0,r1,junk,junk);
			if(r0 == -1)
			{
				if(oldr1 - (c-1) < 0)
				{
					set(0,0,c0,c1);
					set(c-1,c-1,c0,c1);
					set(0,c-1,c0,c0);
					set(0,c-1,c1,c1);
				}
				else
				{
					set(oldr1-(c-1),oldr1-(c-1),c0,c1);
					set(oldr1,oldr1,c0,c1);
					set(oldr1-(c-1),oldr1,c0,c0);
					set(oldr1-(c-1),oldr1,c1,c1);
				}
				print();
			}
			//else if(oldr0 < r0 || r1 < oldr1) impossible();
			else if(r0 == r1)
			{
				if(r0 - (c-1) >= 0)
				{
					set(r0-(c-1),r0-(c-1),c0,c1);
					set(r0,r0,c0,c1);
					set(r0-(c-1),r0,c0,c0);
					set(r0-(c-1),r0,c1,c1);
					print();
				}
				else if(r0 + (c-1) < R)
				{
					set(r0,r0,c0,c1);
					set(r0+(c-1),r0+(c-1),c0,c1);
					set(r0,r0+(c-1),c0,c0);
					set(r0,r0+(c-1),c1,c1);
					print();
				}
				else impossible();
			}
			else impossible();
		}
	}
}
