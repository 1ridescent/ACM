#include <iostream>
#include <deque>
#include <vector>

using namespace std;

deque<int> B;
vector<char> S;

void collapse()
{
	while(true)
	{
		if(B.size() <= 1) return;
		else if(B[0] == B[1])
		{
			int x = B.front();
			B.pop_front();
			B.pop_front();
			B.push_front(2 * x);
		}
		else if(B[B.size() - 1] == B[B.size() - 2])
		{
			int x = B.back();
			B.pop_back();
			B.pop_back();
			B.push_back(2 * x);
		}
		else return;
	}
}

void Left(int x)
{
	B.push_front(x);
	S.push_back('l');
	collapse();
}
void Right(int x)
{
	B.push_back(x);
	S.push_back('r');
	collapse();
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		B.clear();
		S.clear();

		int N;
		cin >> N;
		while(N--)
		{
			int x;
			cin >> x;
			if(B.size() <= 1) Left(x);
			else
			{
				int l = B.front(), r = B.back();
				if(l <= r)
				{
					if(x <= l) Left(x);
					else Right(x);
				}
				else
				{
					if(x <= r) Right(x);
					else Left(x);
				}
			}
		}

		if(B.size() == 1)
		{
			for(int i = 0; i < S.size(); i++)
				cout << S[i];
			cout << '\n';
		}
		else cout << "no\n";
	}
}
