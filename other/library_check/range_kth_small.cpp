#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct BitCnt {
    vector<unsigned long long> blk; // blk 维护一行一行的bit
    vector<unsigned int> cnt;
    BitCnt() {}
    void resize(const unsigned int n) { blk.resize(((n + 1) >> 6) + 1, 0); cnt.resize(blk.size(), 0);}
    void set(const unsigned int i, const unsigned long long x) { blk[i >> 6] |= (x << (i & 63));}
    void init() { for(int i = 1; i < blk.size(); i++) cnt[i] = cnt[i-1] + __builtin_popcountll(blk[i-1]);}
    unsigned int cnt1(int i) const {  // [0, i) 1的个数
        return cnt[i >> 6] + __builtin_popcountll(blk[i >> 6] & ((1ULL << (i & 63)) - 1ULL));
    }
    unsigned int cnt1(int i, int j) const { return cnt1(j) - cnt1(i);} // [i, j) 1的个数
    unsigned int cnt0(int i) const { return i - cnt1(i); } // [0, i) 0的个数
    unsigned int cnt0(int i, int j) const { return cnt0(j) - cnt0(i);} // [i, j) 0的个数
};
struct WaveletMat {
    unsigned int height;
    vector<BitCnt> B;
    vector<int> pos;
    WaveletMat() {}
    WaveletMat(vector<int> A): WaveletMat(A, *max_element(A.begin(), A.end()) + 1) {}
    WaveletMat(vector<int> A, int K) { init(A, K);} // K 字母表大小,数字序列的话是数的种类
    void init(vector<int>& A, int K) {
        height = (K == 1) ? 1 : (64 - __builtin_clzll(K - 1));
        B.resize(height), pos.resize(height);
        for (unsigned int i = 0; i < height; ++i) {
            B[i].resize(A.size());
            for (unsigned int j = 0; j < A.size(); ++j) B[i].set(j, get(A[j], height - i - 1));
            B[i].init();
            auto it = stable_partition(A.begin(), A.end(), [&](int c) {
                return !get(c, height - i - 1);
            });
            pos[i] = it - A.begin();
        }
    }
    int get(const int val, const int i) { return val >> i & 1; } 
    int rank(int l, int r, int x) { return rank(r, x) - rank(l, x);}  // [l, r) 中x出现的频率
    int rank(int i, int val) { // [0, i) 中val出现的频率 
        int p = 0;
        for (unsigned int j = 0; j < height; ++j) {
            if (get(val, height - j - 1)) p = pos[j] + B[j].cnt1(p), i = pos[j] + B[j].cnt1(i);
            else p = B[j].cnt0(p), i = B[j].cnt0(i);
        }
        return i - p;
    }
    int kth(int k, int l, int r) {  // [l, r) 中k小
        int res = 0;
        for (unsigned int i = 0; i < height; ++i) {
            const int j = B[i].cnt0(l, r);
            if (j > k) { l = B[i].cnt0(l), r = B[i].cnt0(r);
            } else {
                l = pos[i] + B[i].cnt1(l), r = pos[i] + B[i].cnt1(r);
                k -= j;
                res |= (1 << (height - i - 1));
            }
        }
        return res;
    }
    int rangefreq(int i, int j, int a, int b, int l, int r, int x) {
        if (i == j || r <= a || b <= l) return 0;
        const int mid = (l + r) >> 1;
        if (a <= l && r <= b) return j - i;
        int left = rangefreq(B[x].cnt0(i), B[x].cnt0(j), a, b, l, mid, x + 1);
        int right = rangefreq(pos[x] + B[x].cnt1(i), pos[x] + B[x].cnt1(j), a, b, mid, r, x + 1);
        return left + right;
    }
    int rangefreq(int l, int r, int a, int b) {  // [l,r) 在[a, b) 值域的数字个数
        return rangefreq(l, r, a, b, 0, 1 << height, 0);
    }
    int rangemin(int i, int j, int a, int b, int l,int r, int x, int val) {
        if (i == j || r <= a || b <= l) return -1;
        if (r - l == 1) return val;
        int mid = (l + r) >> 1;
        int res = rangemin(B[x].cnt0(i), B[x].cnt0(j), a, b, l, mid, x + 1, val);
        if (res < 0)
            return rangemin(pos[x] + B[x].cnt1(i), pos[x] + B[x].cnt1(j), a, b, mid,
                                            r, x + 1, val + (1 << (height - x - 1)));
        else
            return res;
    }
    int rangemin(int l, int r, int a, int b) {  // [l,r) 在[a,b) 值域内存在的最小值是什么，不存在返回-1
        return rangemin(l, r, a, b, 0, 1 << height, 0, 0);
    }
};

template <class T>
struct Discrete {
    vector<T> xs;
    Discrete(const vector<T>& v) {
        xs = v;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }
    int get(const T& x) const {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    inline int operator()(const T& x) const { return get(x); }
    T operator[](int i) { return xs[i]; }
    int size() const { return xs.size(); }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    Discrete v(a);
    for (int i = 0; i < n; ++i) {
        a[i] = v(a[i]);    
    }

    WaveletMat wm(a);

    int l, r, k;
    while (q--) {
    	cin >> l >> r >> k;
    	cout << v[wm.kth(k, l, r)] << '\n';
    }

    return 0;
}
