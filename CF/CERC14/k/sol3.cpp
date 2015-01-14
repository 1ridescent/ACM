// Author: Arkadiusz Pawlik
// Greedy - replace elements in the solution, always trying to improve.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<pair<int, int> > data;
int n;

int chochlik(const vector<pair<int, int>> &a) {
  int cost_so_far = 0;
  int result = INT_MAX;
  for (int i = 0; i < a.size(); ++i) {
    result = min(result, a[i].first - a[i].second - cost_so_far);
    cost_so_far += a[i].second;
  }
  return result;
}

void test() {
  int k;
  cin >> n >> k;
  data.clear();
  for (int i = 0; i < n; ++i) {
    int v, c;
    cin >> v >> c;
    data.push_back(make_pair(v, c));
  }
  sort(data.begin(), data.end());
  if (k >= n) {cout << 0 << endl;return;}
  vector<pair<int, int> > state;
  for (int i = n-k-1; i < n; ++i) {
    state.push_back(data[i]);
  }
  for (int i = n-k-2; i >= 0; --i) {
    vector<pair<int, int>> state2 = state;
    for (int j = 0; j <= k; ++j) {
      vector<pair<int, int>> new_state;
      new_state.push_back(data[i]);
      for (int z = 0; z <= k; ++z) if (z != j) new_state.push_back(state[z]);
      if (chochlik(state2) < chochlik(new_state)) state2 = new_state;
    }
    state = state2;
  }
  cout << max(0,chochlik(state)) << endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  int Z;
  cin >> Z;
  while (Z--) {
    test();
  }
}
