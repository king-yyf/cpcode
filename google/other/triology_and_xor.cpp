#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct FenwickTree2D{
    vector<vector<T>> tr;
    int n, m;
    FenwickTree2D(int N, int M) : n(N), m(M), tr(N, vector<T>(M, 0)){}

    void add(int x, int y, int val){ // 0 <= x < n, 0 <= y < m
        for(int i = x + 1; i <= n; i += i & -i)
            for(int j = y + 1; j <= m; j += j & -j)
                tr[i - 1][j - 1] += val;
    }
 
    T ask(int x, int y) { // 0 <= x < n, 0 <= y < m
        T ret = 0;
        for(int i = x + 1; i > 0; i -= i & -i)
            for(int j = y + 1; j > 0; j -= j & -j)
                ret += tr[i - 1][j - 1];
        return ret;
    }
    T ask(int x1, int y1, int x2, int y2) {  // sum[x1..x2, y1..y2]
        return ask(x2, y2) - ask(x2, y1 - 1) - ask(x1 - 1, y2) + ask(x1 - 1, y1 - 1);
    }
};


int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    
    int n, q;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    	cin >> a[i];

    FenwickTree2D<int> t(n, 30);

    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < 30; ++j) 
    		if (a[i] >> j & 1) 
    			t.add(i, j, 1);
    }

    auto get = [&](int l, int r) {
    	int ans = 0;
    	for (int i = 0; i < 30; ++i) {
    		if (t.ask(l, i, r, i) == r - l + 1) ans = ans | (1 << i); 
    	}
    	return ans;
    };

    cin >> q;
    for (int i = 0; i < q; ++i) {
    	int x1, x2, y1, y2;
    	cin >> x1 >> y1 >> x2 >> y2;
    	x1--, x2--, y1--, y2--;
    	cout << (get(x1, y1) ^ get(x2, y2)) << " \n"[i == q - 1];
    }

    return 0;
}
