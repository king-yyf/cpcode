#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-1077
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
    long long s1 = 0, s2 = 0;
    vector<long long> ans(n - k + 1);
    int m = (k + 1) / 2, cnt = 0;
    for (int i = 0; i < n; ++i) {
        while (!minq.empty() && minq.top().second <= i - k) minq.pop();
        while (!maxq.empty() && maxq.top().second <= i - k) maxq.pop();
        int x = a[i];
        if (cnt < m) {
            maxq.push({x, i}), s2 += x;
            minq.push(maxq.top());
            s1 += maxq.top().first, s2 -= maxq.top().first;
            maxq.pop();
            cnt++;
        } else {
            minq.push({x, i}), s1 += x;
            maxq.push(minq.top());
            s2 += minq.top().first, s1 -= minq.top().first;
            minq.pop();
        }
        while (!minq.empty() && minq.top().second <= i - k) minq.pop();
        while (!maxq.empty() && maxq.top().second <= i - k) maxq.pop();
        if (i < k - 1) continue;
        int md = minq.top().first;
        ans[i - k + 1] = m * 1ll * md - s1 + s2 - (k - m) * 1ll *md;
        if (a[i - k + 1] <= minq.top().first) cnt--, s1 -= a[i - k + 1];
        else s2 -= a[i - k + 1];
    }

    for (auto &x : ans) 
        cout << x << ' ';
    
    return 0;
}
