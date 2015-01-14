#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	while(true)
	{
		char c;
		cin >> c;
		if(c == 'e') return 0;
		if(c == 't')
		{
			cin >> c >> c;
			int r;
			cin >> r;
			int x;
			cin >> x;
			if(x == 0)
			{
				cout << "0\n";
				continue;
			}
			vector<int> t;
			int s = 1;
			for(; x; s *= -r)
			{
				int k = 0;
				while(x % (s * r) != 0)
				{
					x -= s;
					k++;
				}
				t.push_back(k);
			}
			for(int i = t.size() - 1; i >= 0; i--) cout << t[i];
			cout << '\n';
			/*while(abs(s * r) < abs(x)) s *= -r;
			//cout << s << endl;
			for(; s; s /= -r)
			{
				int k = 0;
				while((s > 0 && x > 0) || (s < 0 && x < 0))
				{
					k++;
					x -= s;
				}
				cout << k;
			}
			cout << '\n';*/
		}
		else if(c == 'f')
		{
			cin >> c >> c >> c >> c;
			int r;
			cin >> r;
			string x;
			cin >> x;
			int s = 1;
			int t = 0;
			for(int i = x.size() - 1; i >= 0; i--)
			{
				t += s * (x[i] - '0');
				s *= -r;
			}
			cout << t << '\n';
		}
	}
}
