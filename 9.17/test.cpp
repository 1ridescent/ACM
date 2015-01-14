#include <iostream>

using namespace std;

int main()
{
for(int i = 11233; i <= 33211; i++)
{
int a[10];
a[1] = a[2] = a[3] = 0;;
for(int j = i; j > 0; j /= 10) a[j % 10]++;
if(a[1] == 2 && a[2] == 1 && a[3] == 2) cout << i << endl;
}
}
