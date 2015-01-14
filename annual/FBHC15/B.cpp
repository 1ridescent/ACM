#include <iostream>

using namespace std;

int A[3];
int B[22][3];

int main()
{
	int T;
	cin >> T;
	for(int t = 1 ;t <= T; t++)
	{
		cin >> A[0] >> A[1] >> A[2];
		int N;
		cin >> N;
		for(int i = 0; i < N; i++)
			cin >> B[i][0] >> B[i][1] >> B[i][2];
		string ans = "no";
		for(int b = 0; b < (1 << N); b++)
		{
			int C[3];
			C[0] = C[1] = C[2] = 0;
			for(int i = 0; i < N; i++)
			{
				if(b & (1 << i))
				{
					C[0] += B[i][0];
					C[1] += B[i][1];
					C[2] += B[i][2];
				}
			}
			if(C[0] == A[0] && C[1] == A[1] && C[2] == A[2])
			{
				ans = "yes";
			}
		}
		cout << "Case #" << t << ": " << ans << '\n';
	}
}
