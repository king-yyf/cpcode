#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-1631
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
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    long long s = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
        s += a[i];
        mx = a[i] > mx ? a[i] : mx;    
    }
    cout << max(mx * 2, s) << '\n';
    return 0;
}
