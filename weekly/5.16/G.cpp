#include <bits/stdc++.h>
using namespace std;
int L[35], inside[35], A[36];
char outp[15];
bool ask(string s) {
	cout << "? " << s << endl;
	fflush(stdout);
	scanf("%s", outp);
	return outp[0] == 'Y';
}
bool cmp(int a, int b) {
	return L[a] < L[b];
}
int main() {
	// Find lengths of each character
	int n = 0;
	for (int i = 0; i < 26; ++i) {
		string s;
		for (int j = 1;; ++j) {
			s += 'a' + i;
			if (!ask(s)) break;
			L[i] = j;
		}
		n += L[i];
	}
	for (int i = 0; i < 26; ++i) A[i] = i;
	string prefix;
	for (int i = 0; i < n; ++i) {
		sort(A, A + 26, cmp);
		int cur = A[0];
		for (int j = 1; j < 26; ++j) {
			string t;
			for (int k = 0; k <= inside[A[j]]; ++k)
				t += 'a' + A[j];
			for (int k = 0; k < L[cur]; ++k)
				t += 'a' + cur;
			if (ask(t)) cur = A[j];
		}
		--L[cur];
		++inside[cur];
		prefix += 'a' + cur;
	}
	cout << "! " << prefix << endl;
	fflush(stdout);
}