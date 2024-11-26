#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 从大到小返回一个数组所有子集和的前k大和
// n<=1e5, -1e9 <= a[i] <= 1e9, k <= 2000

typedef pair<long long, int> pli;
vector<long long> kMaxsum(vector<int> &a, int k) {
    int n = a.size();
    long long s = 0, sn = 0;
    for (int &x : a)  {
        s += x;
        if (x < 0) sn += x, x = -x;
    }
    sort(a.begin(), a.end());
    vector<long long> ans{s - sn};
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({a[0], 0});
    for (int i = 2; i <= k; ++i) {
        auto [x, y] = pq.top(); pq.pop();
        ans.push_back(s - sn - x);
        if (y == n -  1) continue;
        pq.push({x + a[y + 1], y + 1});
        pq.push({x + a[y + 1] - a[y], y + 1});
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    auto p = kMaxsum(a, k);
    for (auto &x : p) {
    	cout << x << " ";
    }

    return 0;
}
