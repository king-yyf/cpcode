#include "bits/stdc++.h"
using namespace std;
using i64 = int64_t;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    int n;
    string s;
    cin >> n >> s;
    if (n == 2) {
      if (s[0] != s[1]) {
        cout << "-1\n";
      } else {
        cout << s[0] - 'a' << "\n";
      }
      continue;
    }
    vector<int> a;
    int sum = 0;
    for (char c : s) {
      sum += c - 'a';
      a.push_back(c - 'a');
    }
    if (sum % 2) {
      cout << "-1\n";
      continue;
    }
    sort(a.begin(), a.end());
    while (a.back() * 2 > sum) {
      sum += 26;
      a[0] += 26;
      sort(a.begin(), a.end());
    }
    cout << sum / 2 << "\n";
  }
}