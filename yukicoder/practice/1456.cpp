#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    vector<int> s(n + 1);
    unordered_set<int> st;
    st.insert(0); 
    for (int i = 0; i < n; ++i) {
        s[i + 1] = s[i] ^ a[i];
        if (st.count(s[i + 1] ^ k)) {
        	cout << "Yes\n";
        	return 0;
        }
        st.insert(s[i + 1]);
    }

    cout << "No\n";

    return 0;
}
