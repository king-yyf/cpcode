#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-2428
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
    long long s = 0;
    map<int, int> mp;
    for (int i = 0, j = 0; j < n; ++j) {
        mp[a[j]]++;
        while (mp.size() > k) {
            mp[a[i]]--;
            if (mp[a[i]] == 0) mp.erase(a[i]);
            i++;
        }
        s += j - i + 1;
    }
    cout << s << '\n';
    return 0;
}
