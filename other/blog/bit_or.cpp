#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a) {
	for (int x : a) {
		cout << x << ' ';
	}
	cout << '\n';
}

template <typename T> void fwt(vector<T> &f) {
    int n = f.size();
    for(int i = 1; i < n; i <<= 1) {
        for(int j = 0; j < n; j++) {
            if((j & i) == 0) {
                T x = f[j], y = f[j | i];
                f[j] = x + y, f[j | i] = x - y;
            }
        }
    }
}
template <typename T> void ifwt(vector<T> &f) {
    int n = f.size();
    for(int i = 1; i < n; i <<= 1) {
        for(int j = 0; j < n; j++) {
            if((j & i) == 0) {
                T x = f[j], y = f[j | i];
                f[j] = (x + y) / 2, f[j | i] = (x - y) / 2;
            }
        }
    }
}

template <typename T> void xor_conv(vector<T>& f, vector<T>& g, bool same = true) {
    // int n = 1;
    // while(n < max(f.size(), g.size())) n <<= 1;
    // f.resize(n), g.resize(n);
    fwt(f); if(!same) fwt(g);
    for(int i = 0; i < f.size(); ++i) f[i] *= same ? f[i] : g[i];
    ifwt(f);
}

class Solution {
public:
    int countPairs(vector<int>& a, int low, int high) {
    	int n = 1<<15, ans=0;
        vector<int> b(n);
        for(int x:a){
            b[x]++;
        }
        xor_conv(b, b);
        
        for (int i = low; i <= high && i < n; ++i) {
        	ans += b[i];
        }
        return ans / 2;
    }
};



int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    vector<int> a {1,4,2,7};
    Solution so;
    auto p = so.countPairs(a, 2, 6);

    cout << p << '\n';

    return 0;
}
