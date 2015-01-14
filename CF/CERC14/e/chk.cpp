// Author: Arkadiusz Pawlik
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;

void collapse(vector<int> &numbers) {
  if (numbers.size() < 2) return;
  if (numbers[numbers.size()-2] == numbers[numbers.size()-1]) {
    numbers.pop_back();
    numbers.back() *= 2;
    collapse(numbers);
  }
}

bool viable(const vector<int> &numbers) {
  for (int i = 1; i < (int)numbers.size() - 1; ++i)
    if (numbers[i] < numbers[i-1] && numbers[i] < numbers[i+1])
      return false;
  return true;
}

int main(int argc, char **argv) {
  ifstream in(argv[1]);
  ifstream hintf(argv[2]);
  ifstream out(argv[3]);
  int Z, tn=0;
  in >> Z;
  vector<int> data;
  while (Z--) {
    int n;
    tn+=2;
    in >> n;
    data.clear();
    while (n--) {
      int k;
      in >> k;
      data.push_back(k);
    }
    string hint, sol;
    hintf >> hint;
    out >> sol;
    if (sol != "no") {
      assert(sol.size() == data.size());
      for (int i = 0; i < sol.size(); ++i) {
        assert(sol[i] == 'l' || sol[i] == 'r');
      }
    }
    if(hint == "no" && sol != "no") {
      std::clog << "error in test starting in line " << tn << endl;
      exit(1);
    }
    if(hint != "no" && sol == "no") {
      std::clog << "error in test starting in line " << tn << endl;
      exit(1);
    }
    if (sol == hint) continue;
    vector<int> numbers;
    for (int i = 0; i < data.size(); ++i) {
      if (sol[i] == 'l') {
        reverse(numbers.begin(), numbers.end());
        numbers.push_back(data[i]);
        collapse(numbers);
        reverse(numbers.begin(), numbers.end());
      } else {
        numbers.push_back(data[i]);
        collapse(numbers);
      }
      assert(viable(numbers));
    }
    if(numbers.size() != 1) {
      std::clog << "did not reduce " << tn << endl;
      exit(1);
    }
  }
  cout << "OK\n";
}
