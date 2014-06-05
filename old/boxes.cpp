#include <iostream>

using namespace std;

int N;
int B[111];

int best(int x) // smallest size >= x
{
	int b = 123123, bi = -1;
	for(int i = 0; i < N; i++)
	{
		if(B[i] >= x && B[i] < b)
		{
			b = B[i], bi = i;
		}
	}
	return bi;
}
bool done()
{
	for(int i = 0; i < N; i++) if(B[i] != -1) return false;
	return true;
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> B[i];
	int total = 0;
	while(1)
	{
		int size = 0;
		for(int i = 0; i < N; i++)
		{
			int bi = best(size);
			if(bi == -1)
			{
				break;
			}
			B[bi] = -1;
			size++;
		}
		total++;
		if(done()) break;
	}
	cout << total;
	return 0;
}
