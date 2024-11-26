/**
 *    author:  tourist
 *    created: 12.05.2023 11:21:14       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, k, x, m;
  cin >> n >> k >> x >> m;
  vector<int> l(n), r(n);
  for (int i = 0; i < n; i++) {
    cin >> l[i] >> r[i];
  }
  vector<int> pts;
  for (int i = 0; i < n; i++) {
    pts.push_back(min(l[i], x - m));
    pts.push_back(max(0, r[i] - m));
  }
  pts.push_back(-m);
  pts.push_back(x);
  sort(pts.begin(), pts.end());
  pts.resize(unique(pts.begin(), pts.end()) - pts.begin());
  int sz = (int) pts.size();
  vector<vector<int>> at(sz);
  auto Inter = [&](int i, int j) {
    int l1 = pts[i];
    int r1 = pts[i] + m;
    int l2 = l[j];
    int r2 = r[j];
    return max(0, min(r1, r2) - max(l1, l2));
  };
  vector<vector<long long>> hor(sz, vector<long long>(sz));
  vector<vector<long long>> ver(sz, vector<long long>(sz));
  for (int i = 0; i < n; i++) {
    int cut = (int) (lower_bound(pts.begin(), pts.end(), l[i] + 1) - pts.begin());
    vector<int> val(sz);
    for (int j = 0; j < sz; j++) {
      val[j] = Inter(j, i);
    }
    int a = cut - 1;
    int b = cut;
    while (a >= 0 && b < sz) {
      if (val[a] > val[b]) {
        hor[a][b] += val[a];
        a -= 1;
      } else {
        ver[0][b] += val[b];
        ver[a + 1][b] -= val[b];
        b += 1;
      }
    }
  }
  for (int i = 0; i < sz; i++) {
    for (int j = 0; j < sz - 1; j++) {
      hor[i][j + 1] += hor[i][j];
    }
  }
  for (int j = 0; j < sz; j++) {
    for (int i = x; i < sz - 1; i++) {
      ver[i + 1][j] += ver[i][j];
    }
  }
  for (int i = 0; i < sz; i++) {
    for (int j = 0; j < sz; j++) {
      hor[i][j] += ver[i][j];
    }
  }
  auto Get = [&](long long add) {
    const long long inf = (long long) 1e18;
    vector<pair<long long, int>> dp(sz, make_pair(-inf, 0));
    dp[0] = make_pair(0, 0);
    for (int i = 0; i < sz - 1; i++) {
      for (int t = i + 1; t < sz; t++) {
        dp[t] = max(dp[t], make_pair(dp[i].first + hor[i][t] + add, dp[i].second - 1));
      }
    }
    return dp[sz - 1];
  };
  long long low = (long long) -1e14;
  long long high = (long long) 1e14;
  while (low < high) {
    long long mid = (low + high + 1) >> 1;
    auto got = Get(mid);
    if (-got.second <= k + 1) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }
  auto got = Get(low);
  auto dp = got.first + got.second * low;
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += r[i] - l[i];
  }
  long long extra = (long long) m * n - dp;
  ans += extra;
  cout << (long long) x * n - ans << '\n';
  return 0;
}