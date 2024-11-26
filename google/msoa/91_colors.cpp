#include<bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

void solve() {
	int n, k, x;
	cin >> n >> k >> x;
	vector<long long> dp(n + 1);
	dp[0] = 1, dp[1] = k;
	for (int i = 2; i <= n; ++i) {
		dp[i] = (dp[i - 1] * (k - 1)) % mod;
		if (x <= k) dp[i] = (dp[i] + dp[i - 2]) % mod; \
	}
	cout << dp[n] << "\n";
}


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
int op(int x,int y) {return max(x,y);}



class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& a, int x, int y) {
    	int n = a.size();

    	vector<int> lmx(n, -1), rmx(n, n);
	    stack<int> sk;
	    for (int i = 0; i < n; ++i) {
	        while(!sk.empty() && a[sk.top()] < a[i]) {
	            rmx[sk.top()] = i;
	            sk.pop();
	        }
	        sk.push(i);
	    }
	    sk = stack<int>();
	    for (int i = n - 1; i >= 0; --i) {
	        while (!sk.empty() && a[sk.top()] <= a[i]) {
	            lmx[sk.top()] = i;
	            sk.pop();
	        }
	        sk.push(i);
	    }
	    int ans = 0;

    	for (int i = 0; i < n; ++i) {
    		// 以第i个为最大元素
    		if (a[i] < x) continue;
    		if (a[i] >= x && a[i] <= y) {
    			ans = ans + rmx[i] - lmx[i] - 1;
    		} else {
    			
    		}
    	}
    	return ans;
    }
};

int main() {

	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(20);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}