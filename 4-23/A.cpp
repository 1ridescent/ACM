#include <iostream>
#include <vector>

using namespace std;

vector<int> B, E;

int main()
{
	{
		int b, e;
		cin >> b >> e;
		while(b--)
		{
			int l;
			char d;
			cin >> l >> d;
			while(l--) B.push_back(d == 'L' ? -1 : 1);
		}
		while(e--)
		{
			int l;
			char d;
			cin >> l >> d;
			while(l--) E.push_back(d == 'L' ? -1 : 1);
		}
	}
	int maxt = max(B.size(), E.size());
	while(B.size() < maxt) B.push_back(0);
	while(E.size() < maxt) E.push_back(0);

	int b = 0, e = 0;
	bool meet = true;
	int cnt = 0;
	for(int i = 0; i < maxt; i++)
	{
		b += B[i];
		e += E[i];
		if(b != e) meet = false;
		else
		{
			if(!meet) cnt++;
			meet = true;
		}
	}
	cout << cnt << endl;
}
