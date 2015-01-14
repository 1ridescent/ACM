#include <iostream>
#include <vector>

using namespace std;

int N = 2, K;
char G[1010][1010];

void set(int i, int j)
{
	G[i][j] = G[j][i] = 'Y';
}

int end;
int D = 1;
void Double()
{
	int a = ++N, b = ++N, c = ++N;
	set(end, a);
	set(end, b);
	set(a, c);
	set(b, c);
	end = c;
	D += 2;
}
void One()
{
	int prev = 1;
	for(int i = 0; i < D-1; i++)
	{
		set(prev, ++N);
		//cout << N << ' ';
		prev = N;
	}
	set(prev, end);
}

int main()
{
	for(int i = 0; i < 1010; i++) for(int j = 0; j < 1010; j++) G[i][j] = 'N';
	ios::sync_with_stdio(0);
	cin >> K;
	vector<int> Kbits;
	while(K > 0)
	{
		Kbits.push_back(K%2);
		K /= 2;
	}
	set(1, ++N);
	end = N;
	D = 1;
	for(int i = Kbits.size()-1; i >= 0; i--)
	{
		if(i != Kbits.size()-1) Double();
		if(Kbits[i] == 1) One();
	}
	set(end, 2);
	cout << N << endl;
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= N; j++) cout << G[i][j];
		cout << endl;
	}
	return 0;
}
