#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    string s;
    FenwickTree2D<int> f(n, n);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        for (int j = 0; j < n; ++j) {
        	if (s[j] == '*') f.add(j, i, 1);
        }
    }
    for (int i = 0, y1,x1,y2,x2; i < m; ++i) {
        cin>>y1>>x1>>y2>>x2;
        y1--,x1--,y2--,x2--;
        cout<<f.ask(x1,y1,x2,y2)<<'\n';
    }

    return 0;
}
