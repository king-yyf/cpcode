#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-1076
using ll = long long;

void wt(vector<ll> &a){
    for(auto&x:a){
        cout<<x<<' ';
    }
    cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    using PI = pair<int,int>;
    priority_queue<PI> minq;
    priority_queue<PI, vector<PI>, greater<PI>> maxq;
    vector<int> ans(n - k + 1);
    int m = (k + 1) / 2, cnt = 0;
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        if (cnt < m) {
            maxq.push({x, i});
            minq.push(maxq.top());
            maxq.pop();
            cnt++;
        } else {
            minq.push({x, i});
            maxq.push(minq.top());
            minq.pop();
        }
        while (!minq.empty() && minq.top().second <= i - k) minq.pop();
        while (!maxq.empty() && maxq.top().second <= i - k) maxq.pop();
        if (i < k - 1) continue;
        ans[i - k + 1] = minq.top().first;
        if (a[i - k + 1] <= minq.top().first) cnt--;
    }

    for (auto &x : ans) 
        cout << x << ' ';
    
    return 0;
}
