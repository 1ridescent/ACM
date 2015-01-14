#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, C;
int notes[20020];
int badfreq[90];

bool isbad(int left)
{
	int minnote = 12312322;
	for(int i = left; i < left+C; i++)
	{
		minnote = min(minnote, notes[i]);
	}
	int notefreq[90];
	for(int i = 0; i < 90; i++) notefreq[i] = 0;
	for(int i = 0; i < C; i++) notefreq[notes[left+i] - minnote]++;
	for(int i = 0; i < 90; i++) if(notefreq[i] != badfreq[i]) return false;
	return true;
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> notes[i];
	notes[N] = 12341343;
	cin >> C;
	int minbad = 134123123;
	int tempbad[11];
	for(int i = 0; i < C; i++)
	{
		cin >> tempbad[i];
		minbad = min(minbad, tempbad[i]);
	}
	for(int i = 0; i < C; i++) tempbad[i] -= minbad;
	for(int i = 0; i < 90; i++) badfreq[i] = 0;
	for(int i = 0; i < C; i++) badfreq[tempbad[i]]++;
	vector<int> res;
	for(int i = 0; i <= N-C; i++)
	{
		if(isbad(i)) res.push_back(i+1);
	}
	cout << res.size() << endl;
	for(int i=0;i<res.size();i++)cout<<res[i]<<endl;
	return 0;
}
