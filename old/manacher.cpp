#include <iostream>

using namespace std;

const int MAX = 100010;
int pals[2*MAX-1]; // length of pal centered at s[i] is at [2*i]
void find_pals(const string S)
{
	pals[0] = 1, pals[1] = 0;
	for(int d, i = 1; i+2 <= 2 * S.size(); i += d)
	{
		int& p = pals[i];
		int left = (i-p-1)/2, right = (i+p+1)/2;
		while(0 <= left && right < S.size() && S[left] == S[right])
		{
			left--;
			right++;
			p += 2;
		}
		for(d = 1; pals[i-d] < p-d; d++)
			pals[i+d] = pals[i-d];
		pals[i+d] = p-d;
	}
}

int main()
{
	string S;
	cin >> S;
	find_pals(S);
	for(int i = 0; i < 2*S.size()-1;i++) cout << pals[i] << ' ';
	cout << endl;
	return 0;
}
