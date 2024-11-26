#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,m;
    cin>>n>>m;
    vector<int> b(m);
    multiset<int> a;
    for (int i = 0, x; i < n; ++i) {
        cin>>x;
        a.insert(x);	
    }
    for (int i = 0, x; i < m; ++i) {
        cin >> b[i];
    }

    for (int i = 0; i < m; ++i) {
        auto it = a.upper_bound(b[i]);
        int ans = -1;
        if (it != a.begin()) {
        	ans =  *prev(it);
        	a.erase(prev(it));
        }
        cout << ans << '\n';
    }
    return 0;
}
