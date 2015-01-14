// Author: Arkadiusz Pawlik
// Simplest possible solution with state sorting (no bit encoding).

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> data;

typedef pair<char, int> edge;

struct state {
  vector<int> numbers;
  void extend(int my_index, int next_val, vector<pair<state, edge> > *output);
};

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

void state::extend(int my_index, int next_val,
                   vector<pair<state, edge> > *output) {
  pair<state, edge> next;
  next.second.second = my_index;
  next.first.numbers = numbers;
  next.first.numbers.push_back(next_val);
  collapse(next.first.numbers);
  if (viable(next.first.numbers)) {
    next.second.first = 'r';
    output->push_back(next);
  }
  reverse(numbers.begin(), numbers.end());
  numbers.push_back(next_val);
  collapse(numbers);
  if (viable(numbers)) {
    reverse(numbers.begin(), numbers.end());
    next.first.numbers = numbers;
    next.second.first = 'l';
    output->push_back(next);
  }
  vector<int> empty;
  numbers.swap(empty);
}

bool operator<(const state &a, const state &b) {
  return a.numbers < b.numbers;
}

bool state_equal(const pair<state, edge> &a, const pair<state, edge> &b) {
  return a.first.numbers == b.first.numbers;
}

void alg() {
  vector<vector<pair<state, edge> > > pos(data.size()+1);
  pos[0].push_back(make_pair(state(), make_pair('\0', -1)));
  for (int i = 0; i < data.size(); ++i) {
    int next_val = data[i];
    for (int j = 0; j < pos[i].size(); ++j) {
      state &s = pos[i][j].first;
      s.extend(j, next_val, &(pos[i+1]));
    }
    sort(pos[i+1].begin(), pos[i+1].end());
    pos[i+1].resize(unique(pos[i+1].begin(), pos[i+1].end(), state_equal)
                    - pos[i+1].begin());
  }
  if (pos[pos.size()-1].empty()) {
    cout << "no" << endl;
    return;
  }
  string result;
  int idx = -1;
  for (int i = 0; i < pos[pos.size()-1].size(); ++i) {
    if (pos[pos.size()-1][i].first.numbers.size() == 1) {
      idx = i;
      break;
    }
  }
  if (idx == -1) {
    cout << "no" << endl;
    return;
  }
  pair<state, edge> step = pos[pos.size()-1][idx];
  for (int i = pos.size()-1; i > 0; --i) {
    result.push_back(step.second.first);
    step = pos[i-1][step.second.second];
  }
  reverse(result.begin(), result.end());
  cout << result << endl;
}

int main() {
  ios::sync_with_stdio(false);
  int c;
  cin >> c;
  while(c--) {
    int n;
    cin >> n;
    data.clear();
    while (n--) {
      int k;
      cin >> k;
      data.push_back(k);
    }
    alg();
  }
}
