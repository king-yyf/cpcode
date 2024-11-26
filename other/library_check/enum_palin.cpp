#include <bits/stdc++.h>
using namespace std;

// https://judge.yosupo.jp/problem/enumerate_palindromes

using ll = long long;

struct Manacher {
    int n;
    vector<int> d1, d2;
    Manacher() {}
    Manacher(const string &s) {
        vector<int> a(s.begin(), s.end());
        build(a);
    }
    Manacher(vector<int> &a) {build(a);}
    void build(vector<int> &s) {
        n = s.size();
        d1.resize(n); d2.resize(n);
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
            d1[i] = k--;
            if (i + k > r) l = i - k, r = i + k;
        }
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
            d2[i] = k--;
            if (i + k > r) l = i - k - 1, r = i + k;
        }
    }
    pair<int, int> longest_palin() { //最长回文子串<len, 左边界>
        int mx = 0, l;
        for (int i = 0; i < n; ++i) 
            mx = max({mx, 2 * d1[i] - 1, 2 * d2[i]});
        for (int i = 0; i < n; ++i) {
            if (2 * d1[i] - 1 == mx) { l = i - d1[i] + 1; break; }
            if (2 * d2[i] == mx) { l = i - d2[i]; break;}
        }
        return {mx, l};
    }
    bool is_palin(int l, int r) {   // check s[l..(r-1)] 0 <= l <= r < n
        if ((r - l) % 2 == 0) return d2[(l + r) / 2] >= (r - l) / 2;
        return d1[(l + r) / 2] >= (r - l + 1) / 2;
    }
    // 以2n-1个位置(n个字符和n-1个相邻字符点中间)为回文中心的最长回文子串长度
    vector<int> enum_palin() {
        vector<int> ans(2 * n - 1);
        for (int i = 0, j = 0; i < n; ++i) {
            ans[j++] = d1[i] * 2 - 1;
            if (i < n - 1) ans[j++] = d2[i + 1] * 2;
        }
        return ans;
    }
    vector<int> palin_cnt() { // 每个位置开始的回文串数目,i<=j,s[i..j]是回文
        vector<int> c(n);
        c[0] = -1;
        for (int i = 0; i < n; ++i) {
            c[i + 1 - d1[i]]++, c[i - d2[i]]++;
            if (i + 1 < n) c[i + 1] -= 2;
        }    
        for (int i = 1; i < n; ++i) c[i] += c[i - 1];
        return c;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s;
    cin >> s;
    Manacher m(s);
    vector<int> ans = m.enum_palin();
    for (int i = 0, n = ans.size(); i < n; ++i) 
    	cout << ans[i] << " \n"[i == n - 1];
    return 0;
}
