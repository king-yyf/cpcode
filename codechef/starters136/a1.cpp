#include <bits/stdc++.h>
using namespace std;

long long compute_sum(const string& s) {
    int n = s.size();
    long long ans = n * (n + 1LL) / 2; // Total number of substrings
    map<int, int> counts;
    counts[0] = 1;
    int a = 0, b = 0;
    for (char c : s) {
        if (c == '0') {
            a++;
        } else {
            b++;
        }
        int diff = a - b;
        if (counts.find(diff) != counts.end()) {
            ans += counts[diff];
            counts[diff]++;
        } else {
            counts[diff] = 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        cout << compute_sum(s) << endl;
    }

    return 0;
}