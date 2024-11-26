#include <bits/stdc++.h>
using namespace std;

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


long long op(long long x, long long y) {return max(x, y);}
template <class T, T (*op)(T, T)>
class ST {
 public:
  int n;
  vector<vector<T>> mat;
 
  ST(const vector<T>& a) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = op(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
 
  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return op(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};

int n,m,x,y,k,q;
void solve(){
	cin>>n;
	vector<int> a(n);
	for(auto&x: a) cin>>x;
	
    vector<long long> pref(n + 1), suf(n + 1), left(n, -1), right(n, n);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];
    for (int i = n - 1; i >= 0; --i) suf[i] = suf[i + 1] + a[i];
    stack<int> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && a[sk.top()] < a[i]) {
            right[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    sk = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && a[sk.top()] <= a[i]) {
            left[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    ST<long long,op> st1(pref), st2(suf);
    for(int i=0;i<n;++i){
    	int l=left[i]+1,r=right[i]-1;
        long long x=-1e18,y=-1e18;
        if(i+2<=r+1) y=st1.get(i+2,r+1);
        if(l<=i-1) x=st2.get(l,i-1);
    	if(pref[i+1]<y||suf[i]<x){
    		cout<<"NO\n";
    		return;
    	}
    }
    cout<<"YES\n";
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve();
	}
	return 0;
}
