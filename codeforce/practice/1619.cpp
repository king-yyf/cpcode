#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<pair<int,int> > a;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;	
        a.emplace_back(x, 1);
        a.emplace_back(y + 1, -1);
    }
    sort(a.begin(), a.end());

    int mx = 0, cnt = 0;
    for (auto & [x, y] : a) {
    	cnt += y;
    	mx = max(mx, cnt);
    }
    cout << mx << '\n';

    return 0;
}
