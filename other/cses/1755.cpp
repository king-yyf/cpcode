#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s ,t = "";
    cin >> s;
    vector<int> a(26);
    for (auto &c : s) {
    	a[c - 'A']++;
    }
    int cnt = 0, c = 0;
    char ch;
    for (int i = 0; i < 26; ++i) {
        if (a[i] % 2 != 0) {
        	ch = 'A' + i;
        	cnt++;
        	c = a[i];
        }
    }

    if (cnt > 1) {
    	cout << "NO SOLUTION\n";
    	return 0;
    }
    
    for (int i = 0; i < 26; ++i) {
    	int x = a[i];
    	if (x % 2 != 0) continue;
    	for (int j = 0; j < x / 2; ++j) {
    		t += 'A' + i;
    	}
    }

    cout << t;
    if(cnt > 0) cout << string(c, ch);
    reverse(t.begin(), t.end());
    cout << t << "\n";

    return 0;
}
