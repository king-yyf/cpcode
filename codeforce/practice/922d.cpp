#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    vector<int> s(n), h(n);

    for (int i = 0; i < n; ++i) {
    	s[i] = count(a[i].begin(), a[i].end(), 's');
    	h[i] = count(a[i].begin(), a[i].end(), 'h');
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    sort(p.begin(), p.end(), [&](int i, int j){
    	return s[i] * 1ll * h[j] > s[j] * 1ll * h[i];
    });

    long long c = 0, c1 = 0, c2 = 0;

    for (int i = 0; i < n; ++i) {
    	string &s1 = a[p[i]];
    	for (int j = 0; j < s1.size(); ++j) {
    		if (s1[j] == 'h') {
    			c += c1;
    		} else {
    			c1 ++;
    		}
    	}
    }

    cout << c << '\n';

    return 0;
}
