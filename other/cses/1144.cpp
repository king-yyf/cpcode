#include <bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    ordered_set<int> s;
    for (int i = 0; i < n; ++i) {
        cin>>a[i];  
        s.insert(a[i]);
    }

    for (int i = 0; i < q; ++i) {
        char c;
        cin >> c;
        if (c == '!') {
            int k, x;
            cin >> k >> x;
            k--;
            s.erase(s.find_by_order(s.order_of_key(a[k])));
            a[k] = x;
            s.insert(x);
        } else {
            int l, r;
            cin >> l >> r;

            cout << s.order_of_key(r + 1) - s.order_of_key(l) << '\n';
        }
    }
    return 0;
}
