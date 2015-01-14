#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define left Left
#define right Right

int N;
char S[1000100];
long long left[1000100];
long long right[1000100];

inline bool letter(char c)
{
	return ('a' <= c && c <= 'z');
}
inline bool number(char c)
{
	return ('0' <= c && c <= '9');
}

int main()
{
	scanf("%s", &S[1]);
	N = strlen(&S[1]);
	memset(left, 0, sizeof(left));
	memset(right, 0, sizeof(right));
	for(int i = 1; i <= N; i++)
	{
		if(letter(S[i]) || number(S[i]) || S[i] == '_') left[i] = left[i - 1];
		if(letter(S[i])) left[i]++;
	}
	for(int i = N; i >= 1; i--)
	{
		if(letter(S[i])) right[i] = right[i + 1] + 1;
	}
	long long total = 0;
	char prev = '?';
	int loc = -1;
	bool valid = false;
	for(int i = 1; i <= N; i++)
	{
		//cout << prev << ' ' << loc << ' ' << valid << endl;
		if(S[i] == '@')
		{
			prev = '@';
			loc = i;
			valid = true;
		}
		else if(S[i] == '_')
			valid = false;
		else if(S[i] == '.')
		{
			if(prev == '@' && valid && loc + 1 < i) total += left[loc - 1] * right[i + 1];
			prev = '.';
		}
	}
	cout << total << endl;
	return 0;
}
