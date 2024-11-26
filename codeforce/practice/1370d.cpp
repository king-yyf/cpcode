#include <bits/stdc++.h>
using namespace std;

int minCostSubSeq(vector<int> &a, int k) {
    int n = a.size();
    auto chk = [&](int x) {
        for (int d = 0; d < 2; ++d) {
            int len = 0;
            for (int i = 0; i < n; ++i) {
                if (len % 2 != d || a[i] <= x) {
                    len++;
                }
            }
            if (len >= k) return 1;
        }
        return 0;
    };

    int l = 1, r = 1e9, ans = l;

    while (l <= r) {
        int md = (l + r) / 2;
        if (chk(md)) {
            ans = md;
            r = md - 1;
        } else l = md + 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];	
    }
    cout << minCostSubSeq(a, k) << "\n";

    return 0;
}
