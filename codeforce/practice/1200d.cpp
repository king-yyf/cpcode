#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
struct PrefixDiff2D {
    int n, m;
    vector<vector<T>> a;
    PrefixDiff2D(int N, int M) : n(N), m(M), a(N, vector<T>(M, 0)){}
    PrefixDiff2D(vector<vector<T>> &A) {
        n = A.size(), m = A[0].size();
        a.assign(n, vector<T>(m, 0));
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j)
                add(i, j, i, j, a[i][j]);
    }
    void add(int x1, int y1, int x2, int y2, T c) { // sum[x1..x2, y1..y2]
        a[x1][y1] += c;
        if (y2 + 1 < m) a[x1][y2 + 1] -= c;
        if (x2 + 1 < n) a[x2 + 1][y1] -= c;
        if (x2 + 1 < n && y2 + 1 < m) a[x2 + 1][y2 + 1] += c;
    }
    void get() { // 求操作完成后的矩阵
        for (int i = 1; i < n; ++i) a[i][0] += a[i - 1][0];
        for (int j = 1; j < m; ++j) a[0][j] += a[0][j - 1];
        for (int i = 1; i < n; ++i) for (int j = 1; j < m; ++j)
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k, cnt = 0;
    cin >> n >> k;

    vector<string> a(n);
    for (auto &s : a) {
    	cin >> s;
    }

    PrefixDiff2D<int> f(n,n);

    for (int i = 0; i < n; ++i) {
    	int l = -1, r = -1;
    	for (int j = 0; j < n; ++j) {
    		if (a[i][j] == 'B') {
    			r = j;
    			if (l == -1) l = j;
    		}
    	}
    	if (l < 0) cnt++;
    	else if (r - l + 1 <= k){
    		int u = max(0, i - k + 1);
    		int l1 = max(0, r - k + 1);
    		if (l1 <= l) {
    			f.add(u, l1, i, l, 1);
    		}
    	}
    }

    for (int j = 0; j < n; ++j) {
    	int u = -1, d = -1;
    	for (int i = 0; i < n; ++i) {
    		if (a[i][j] == 'B') {
    			d = i;
    			if (u == -1) u = i;
    		}
    	}
    	if (u < 0) cnt++;
    	else {
    		int l = max(j - k + 1, 0);
    		int u1 = max(0, d - k + 1);
    		if (u1 <= u) {
    			f.add(u1, l, u, j, 1);
    		}
    	}
    }

    f.get();

    int ans = 0;

    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < n; ++j) 
    		ans = max(ans, f.a[i][j]); 
    }

    cout << ans + cnt << '\n';

    return 0;
}
