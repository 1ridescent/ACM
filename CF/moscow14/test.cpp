#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
ios::sync_with_stdio(false);
cout << "1000 25673763 9183\n";
for(int i = 0; i < 1000; i++) {
cout << "1000 ";
for(int j = 0; j < 1000; j++) cout << rand() % 777777777 << ' ';
cout << '\n';
}
}
