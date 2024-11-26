#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T, class LF, class RF>
void monoStack(vector<T> &a, vector<int> &lt, vector<int> &rt, LF F1, RF F2) {
    int n = a.size();
    lt.assign(n, -1), rt.assign(n, n);
    stack<int> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && F1(a[i],a[sk.top()])) {
            rt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    sk = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && F2(a[i],a[sk.top()])) {
            lt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
}
template <typename T>  // 左右第一个更小的数，即以当前元素为最小值的区间
void le_le(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, less<T>(), less<T>());
}
template <typename T>  // 左右第一个更小的数，右侧是小于等于
void le_le_eq(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, less<T>(), less_equal<T>());
}
template <typename T> // 左右第一个更大的数，即以当前元素为最大值的区间
void gt_gt(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, greater<T>(), greater<T>());
}
template <typename T> // 左右第一个更大的数，右侧是大于等于
void gt_gt_eq(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, greater<T>(), greater_equal<T>());
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
int op(int x,int y) {return min(x,y);}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n * 3);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    	a[i + n] = a[i + 2 * n] = a[i];
    }

    auto [mn, mx] = minmax_element(a.begin(), a.begin() + n);

    if ((*mn) * 2 >= (*mx)) {
    	for (int i = 0; i < n; ++i) {
    		cout << -1 << " \n"[i == n - 1];
    	}
    	return 0;
    }

    vector<int> lmx, rmx;
    gt_gt_eq(a, lmx, rmx);

    int m = n * 3;
    int id = 0;
    for (int i = 0; i < n; i++) {
    	if (a[i] == (*mx) && a[i] > a[i + 1]) {
    		id = i + n;
    		break;
    	}
    }
    vector<int> c(id + 1);
    ST<int, op> s(a);
    for (int i = id; i >= 0; i--) {
    	int r = rmx[i], l;
    	if (r - 1 < i + 1 || s.get(i + 1, r - 1) * 2 >= a[i]) {
    		c[i] = c[i + 1];
    		continue;
    	}
    	l = i + 1, r = rmx[i] - 1;
    	int fst = r;
    	while (l <= r) {
    		int md = (l + r) / 2;
    		if (s.get(i + 1, md) * 2 < a[i]) {
    			fst = md;
    			r = md - 1;
    		} else l = md + 1;
    	}
    	c[i] = fst;
    }

    for (int i = 0; i < n; ++i) {
    	cout << c[i] - i << " \n"[i == n - 1];
    }

    return 0;
}
