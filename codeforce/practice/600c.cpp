#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve(string s) {
    map<char, int> mp;
    for (char c : s) mp[c]++;
    vector<char> p;
    for (auto &[k, v] : mp) {
        if (v & 1) p.push_back(k);
    }
    int i = 0, j = p.size() - 1;
    while (i < j) {
        mp[p[i]]++;
        mp[p[j]]--;
        i++;
        j--;
    }
    string ans, t;
    for (char c = 'a'; c <= 'z'; ++c) {
        if (mp[c] % 2 == 0) {
            ans += string(mp[c] / 2, c);
        }else {
            ans += string(mp[c] / 2, c);
            t = string(1, c);
        }
    }
    cout<<ans<<t;
    reverse(ans.begin(),ans.end());cout<<ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s;
    cin>>s;
    solve(s);
    return 0;
}
