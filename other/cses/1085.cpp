#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-1085
using ll = long long;

void wt(vector<ll> &a){
    for(auto&x:a){
        cout<<x<<' ';
    }
    cout<<'\n';
}

// https://vjudge.net/problem/CSES-1631

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    auto chk = [&](long long x) {
        int cnt = 1;
        long long s = 0;
        for (int i = 0; i < n; ++i) {
            if (s + a[i] > x) {
                cnt++;
                s = a[i];
            }else s += a[i];
        }
        return cnt <= k;
    };

    long long l = (*max_element(a.begin(), a.end())), r = accumulate(a.begin(), a.end() , 0ll), ans = r;
    while (l <= r) {
        long long md = (l + r) / 2;
        if (chk(md)) {
            ans = md;
            r = md - 1;
        } else l = md + 1;
        
    }
    cout << ans << '\n';
    return 0;
}
