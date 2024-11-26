#include <bits/stdc++.h>
using namespace std;

int minStringCost(string& s) {
    int n = s.size();
    vector<int> s1(n + 1), p;
    for (int i = 0; i < n; ++i) {
        s1[i + 1] = s1[i] + (s[i] == '0');
        if (s[i] == '1') p.push_back(i);
    }
    int m = p.size(), l = 0, r = m, ans = m;
    while (l < r) {
        int md = (l + r) / 2;
        bool ok = 0;
        for (int i = 0; i <= md; ++i) {
            int l1 = p[i], r1 = p[m - 1 - md + i];
            if (s1[r1 + 1] - s1[l1] <= md) {
                ok = 1;
            } 
        }
        if (ok) r = md;
        else l = md + 1;
    }
    return l;
}

int minStringCost1(string& s) {
    int n = s.size(), x = 0, y = 0, ans = n;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') x++;
        else y++;
    }
    int x1 = 0, y1 = y, j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < n && x1 < y1) {
            if (s[j] == '0') x1++;
            else y1--;
            j++;
        }
        ans = min(ans, max(x1, y1));
        if (s[i] == '0') x1--;
        else y1++;
    }
    return ans;
}

int minStringCost2(string& s) {
    int n = s.size();
    vector<int> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + (s[i] == '1');
    }
    if (p[n] == n || p[n] == 0) return 0;
    int res = min(p[n], n - p[n]);
    for (int i = 1; i <= n; ++i) {
        if (i >= p[n]) res = min(res, (i - p[i]) - (i - p[n] - p[i - p[n]]));
        else res = min(res, p[n] - p[i]);
    }
    return res;
}

int main(){
  int t;
  cin >> t;
  for (int i = 0; i < t; i++){
    string s;
    cin >> s;
    cout << minStringCost2(s) << "\n";
  }
}