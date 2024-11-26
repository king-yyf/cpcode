#include <bits/stdc++.h>
using namespace std;
int n, m, q;

// template<typename T>
// struct FenwickTree2D{
//     vector<vector<T>> tr;
//     int n, m;
//     FenwickTree2D(int N, int M) : n(N), m(M), tr(N, vector<T>(M, 0)){}

//     void add(int x, int y, int val){ // 0 <= x < n, 0 <= y < m
//         for(int i = x + 1; i <= n; i += i & -i)
//             for(int j = y + 1; j <= m; j += j & -j)
//                 tr[i - 1][j - 1] += val;
//     }
 
//     T ask(int x, int y) { // 0 <= x < n, 0 <= y < m
//         T ret = 0;
//         for(int i = x + 1; i > 0; i -= i & -i)
//             for(int j = y + 1; j > 0; j -= j & -j)
//                 ret += tr[i - 1][j - 1];
//         return ret;
//     }
//     T ask(int x1, int y1, int x2, int y2) {  // sum[x1..x2, y1..y2]
//         return ask(x2, y2) - ask(x2, y1 - 1) - ask(x1 - 1, y2) + ask(x1 - 1, y1 - 1);
//     }
// };


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



void solve() {
    cin>>n>>m;

    vector a(n,vector<int>(m));

    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j)
            cin>>a[i][j];
    }
    
    int l=1,r=n,c=0;
    while(l<=r){
    	int md=(l+r)/2;
    	bool o=0;
        PrefixSum2D<int> f(n,m);

        vector p(n,vector<int>(m));

        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j) if(a[i][j]>=md)
               p[i][j]=1;
        }
        PrefixSum2D<int> s(p);
    	for(int i=0;i+md<=n;++i){
    		for(int j=0;j+md<=m;++j){
                if(s.sum(i,j,i+md-1,j+md-1)==md*md){
                    o=1;break;
                }
    		}
    	}
    	if(o){
    		c=md;
    		l=md+1;
    	}else r=md-1;
    }
  
    cout<<c<<"\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve();
    }

    return 0;
}
