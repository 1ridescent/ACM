#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>

using namespace std;

typedef deque<int> num;

int N, B;

void print(num a)
{
	for(int i = 0; i < a.size(); i++) cout << a[i] << ' ';
	cout << endl;
}

num convert(int n)
{
	num a;
	for(; n > 0; n /= B) a.push_back(n % B);
	return a;
}
num add(num& a, num& b)
{
	if(a.size() > b.size()) return add(b, a);
	num c;
	int carry = 0;
	for(int i = 0; i < b.size(); i++)
	{
		c.push_back((i < a.size() ? a[i] : 0) + b[i] + carry);
		carry = c[i] / B;
		c[i] %= B;
	}
}
num shift(num a, int i)
{
	while(i--) a.push_front(0);
	return a;
}

vector< pair<num, num> > nexts;
void next(num& a, num& a2)
{
	for(int b = 1; b < B; b++)
	{
		num ba = a, ba2 = a2;

	}
}

vector<num> V[2020];

int main()
{
	cin >> B >> N;
	V[0].push_
}
