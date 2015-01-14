#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <set>

using namespace std;

int N, P;
vector<int> primes;
bool isprime[300005];
void sieve()
{
	memset(isprime, -1, sizeof(isprime));
	for(int i = 2; i <= N; i++)
		if(isprime[i])
		{
			primes.push_back(i);
			for(int j = i + i; j <= N; j += i)
				isprime[j] = false;
		}
}

char interact(int x)
{
	/*cout << x << '\n';
	cout.flush();
	string s;
	if(!(cin >> s)) exit(0);
	if(s == "OK") exit(0);
	return s[0];*/

	cout << "guessing " << x << endl;
	char c;
	if(2 * (x % P) < P) c = '>';
	else c = '<';
	cout << "answer = " << c << '\n';
	return c;
}

vector<int> poss;

vector<int> Left, Right;
int Try(int x)
{
	Left.clear();
	Right.clear();
	cout << "trying " << x << "...\n";
	for(int i = 0; i < poss.size(); i++)
	{
		int p = poss[i];
		if(p == x) continue;
		if(2 * (x % p) < p) Left.push_back(p);
		else Right.push_back(p);
	}
	cout << "left : "; for(int i = 0; i < Left.size(); i++) cout << Left[i] << ' '; cout << endl;
	cout << "right : "; for(int i = 0; i < Right.size(); i++) cout << Right[i] << ' '; cout << endl;
	return max(Left.size(), Right.size());
}

int main()
{
	cin >> N >> P;
	sieve();

	poss = primes;
	for(int t = 0; t < 100; t++)
	{
		if(poss.size() == 1)
		{
			interact(poss[0]);
			return 0;
		}
		int best = 1000000000, best_x = -1;
		for(int i = 0; i < poss.size(); i++)
		{
			int x = poss[i];
			int s = Try(x);
			if(s < best)
			{
				best = s;
				best_x = x;
			}
		}
		Try(best_x);
		interact(best_x);
		char c = interact(2);
		if(c == '>') // left
			poss = Left;
		else
			poss = Right;
		cout << "poss left : "; for(int i = 0; i < poss.size(); i++) cout << poss[i] << ' '; cout << endl;
	}
}
