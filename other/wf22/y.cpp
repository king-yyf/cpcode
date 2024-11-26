#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    string s, t;
    cin >> s;

    for (char c : s) {
    	if (t.empty() || c != t.back()) {
    		t += c;
    	}
    }

    while (t.size() >= 4) {
    	for (int i = 0; i < 2; ++i) 
    		t.pop_back();
    }

    cout << t << '\n';

    return 0;
}
