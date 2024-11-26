#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t; cin >> t; while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& ai : a) {
      cin >> ai;
    }

    // f(b) = max(b) + 1 - len(set(b))

    vector<int> prev_gt(n, -1), prev_eq(n, -1); {
      stack<int> mono;
      for (int i = 0; i < n; ++i) {
        while (!mono.empty() && a[mono.top()] <= a[i]) {
          mono.pop();
        }
        if (!mono.empty()) {
          prev_gt[i] = mono.top();
        }
        mono.push(i);
      }
    }

    vector<int> next_ge(n, n), next_eq(n, n); {
      stack<int> mono;
      map<int, int> mp;
      for (int i = n - 1; i >= 0; --i) {
        if (mp.count(a[i])) {
          next_eq[i] = mp[a[i]];
        }
        mp[a[i]] = i;
        while (!mono.empty() && a[mono.top()] < a[i]) {
          mono.pop();
        }
        if (!mono.empty()) {
          next_ge[i] = mono.top();
        }
        mono.push(i);
      }
    }

    for(int i=0;i<n;++i){
      cout<<prev_gt[i]<<" ";
    }
    cout<<"\n";
    for(int i=0;i<n;++i){
      cout<<next_ge[i]<<" ";
    }
    cout<<"\n";

    int64_t ans = 0;
    int64_t s1 = 0;
    for (int i = 0; i < n; ++i) {
      ans += (i - prev_gt[i]) * (a[i] + 1ll) * (next_ge[i] - i);
      s1 += (i - prev_gt[i])  * (next_ge[i] - i);
      cout << "l = " << (i - prev_gt[i]) << ", r = " << (next_ge[i] - i) << ", s1 = " << s1 << "\n";
      ans -= (i + 1ll) * (next_eq[i] - i);
    }
    cout << s1 << ", " << n * (n + 1) / 2 << '\n';
  }
}