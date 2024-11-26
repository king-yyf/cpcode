#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
	int n;
	cin >> n;
	string s;

	set<string> st, s23, s32;
	bool o = 0;

	for (int i = 0; i < n; ++i) {
		cin >> s;
		auto t = s;
		reverse(t.begin(), t.end());
		if (t == s || st.count(t)) o = 1;
		st.insert(s);
		if (s.size() == 2) {
			s23.insert(t);
			if (s32.count(t)) o = 1;
		}
		if (s.size() == 3) {
			s32.insert(s.substr(0, 2));
			if (s23.count(s.substr(1))) o = 1;
		}
	}
	cout << (o ? "YES" : "NO") << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
    	solve();
    }

    return 0;
}
