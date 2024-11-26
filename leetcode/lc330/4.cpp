#include<bits/stdc++.h>
using namespace std;

template <typename T>
struct PrefixSum2D {
    int n, m;
    vector<vector<T>> a;
    PrefixSum2D(int N, int M) : n(N), m(M), a(N + 1, vector<T>(M + 1, 0)){}
    PrefixSum2D(vector<vector<T>> &A) {
        n = A.size(), m = A[0].size();
        a.assign(n + 1, vector<T>(m + 1, 0));
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j)
                a[i + 1][j + 1] = a[i][j + 1] + a[i + 1][j] - a[i][j] + A[i][j];
    }
    T sum(int x1, int y1, int x2, int y2) { // sum[x1..x2, y1..y2]
        return a[x2 + 1][y2 + 1] - a[x2 + 1][y1] - a[x1][y2 + 1] + a[x1][y1];
    }
};


class Solution {
public:
    long long countQuadruplets(vector<int>& a) {
        int mx = max_element(a.begin(), a.end()), n = a.size();
        vector f(n, vector<int>(mx + 1));
        for (int i = 0; i < n; ++i) {
            f[i][a[i]] = 1;
        }
        PrefixSum2D<int>  p(f);

        long long ans = 0;
        for (int j = 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (a[j] > a[k]) {
                    long long x = p.get(0, 0, j - 1, a[k] - 1), y = p.get(k + 1, a[j] + 1, n - 1, mx);
                    ans += x * y;
                }
            }
        }
        return ans;
    }
};