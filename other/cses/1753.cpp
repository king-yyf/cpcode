#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1753

template <typename T>
vector<int> kmp_table(const T &s) {
    int n = s.size(), k = 0;
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        while (k > 0 && !(s[i] == s[k])) k = p[k - 1];
        if (s[i] == s[k]) k++;
        p[i] = k;
    }
    return p;
}
template <typename T>
vector<int> kmp(const T &s, const T &t) {  // return s在t中所有出现下标
    vector<int> res, p = kmp_table(s);
    int n = s.size(), m = t.size(), k = 0;
    for (int i = 0; i < m; ++i) {
        while (k && (k == n || !(t[i] == s[k]))) k = p[k - 1];
        if (t[i] == s[k]) k++;
        if (k == n) res.push_back(i - n + 1);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s, t;

    cin >> s >> t;

    auto p = kmp(t, s);

    cout << p.size() << '\n';

    return 0;
}
