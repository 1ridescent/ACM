#include <iostream>
#include <cstring>

using namespace std;

int N, M;
char A[105][105];
int nrow[105][105], ncol[105][105], row[105][105], col[105][105];

int main()
{
	memset(A, '.', sizeof(A));
	cin >> N >> M;
	for(int r = 1; r <= N; r++)
		for(int c = 1; c <= M; c++)
		{
			for(char a = 'A'; a <= 'Z'; a++)
			{
				if(A[r - 1][c] == a)
				{

				}
				else
				{
					A[r][c] = a;
					nrow[r][c] = ncol[r][c] = row[r][c] = col[r][c] = 1;
					break;
				}
			}
		}
}
