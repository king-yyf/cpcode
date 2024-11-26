#include <bits/stdc++.h>
using namespace std;

// https://yukicoder.me/problems/no/1013

/*
题意：
给一个1-n的排列，循环无数次。
当处于第i个位置时，设第i个位置的数字是x, 会向右跳x个位置，
输入整数k，求当从第1，2,n个位置出发时，向右跳k次后所到达的位置。
+ 1 <= n <= 1e5
+ 1 <= k <= 1e9
*/

using ll = long long;

template <class S, S (*op)(S, S)> class BiLiftring {
    int n = 0;
    vector<vector<int>> _nexts;
    vector<vector<S>> _prods;

    void build_next() {
        vector<int> t(n);
        vector<S> p(n);

        for (int i = 0; i < n; ++i) {
            if (int j = _nexts.back()[i]; isin(j)) {
                t[i] = _nexts.back()[j], p[i] = op(_prods.back()[i], _prods.back()[j]);
            } else t[i] = j, p[i] = _prods.back()[i];
        }
        _nexts.emplace_back(move(t));
        _prods.emplace_back(move(p));
    }

    inline bool isin(int i) const noexcept { return 0 <= i and i < n; }

public:
    // (up to) 2^d steps from `s`
    // Complexity: O(d) (Already precalculated) / O(nd) (First time)
    int pow_next(int s, int d) {
        assert(isin(s));
        while (int(_nexts.size()) <= d) build_next();
        return _nexts.at(d).at(s);
    }

    // Product of (up to) 2^d elements from `s`
    const S &pow_prod(int s, int d) {
        assert(isin(s));
        while (int(_nexts.size()) <= d) build_next();
        return _prods.at(d).at(s);
    }

    BiLiftring() = default;
    BiLiftring(const vector<int> &g, const vector<S> &w)
        : n(g.size()), _nexts(1, g), _prods(1, w) {
        assert(g.size() == w.size());
    }

    // (up to) k steps from `s`
    template <class Int> int kth_next(int s, Int k) {
        for (int d = 0; k > 0 and isin(s); ++d, k >>= 1) {
            if (k & 1) s = pow_next(s, d);
        }
        return s;
    }

    // Product of (up to) `len` elements from `s`
    template <class Int> S get(int s, Int len) {
        assert(isin(s)); assert(len > 0);
        int d = 0;
        while (!(len & 1)) ++d, len /= 2;

        S ret = pow_prod(s, d);
        s = pow_next(s, d);
        for (++d, len /= 2; len and isin(s); ++d, len /= 2) {
            if (len & 1) ret = op(ret, pow_prod(s, d)), s = pow_next(s, d);
        }
        return ret;
    }

    // `start` から出発して「`left_goal` 以下または `right_goal` 以上」に到達するまでのステップ数
    // 単調性が必要
    int dis_mono(int start, int left_goal, int right_goal) {
        assert(isin(start));

        if (start <= left_goal or right_goal <= start) return 0;

        int d = 0;
        while (left_goal < pow_next(start, d) and pow_next(start, d) < right_goal) {
            if ((1 << d) >= n) return -1; ++d;
        }
        int ret = 0, cur = start;
        for (--d; d >= 0; --d) {
            if (int nxt = pow_next(cur, d); left_goal < nxt and nxt < right_goal) {
                ret += 1 << d, cur = nxt;
            }
        }
        return ret + 1;
    }

    template <class F> long long max_len(const int s, F f, const int maxd = 60) {
        assert(isin(s));
        int d = 0;
        while (d <= maxd and f(pow_prod(s, d))) {
            if (!isin(pow_next(s, d))) return 1LL << maxd; ++d;
        }
        if (d > maxd) return 1LL << maxd;
        --d;
        int cur = pow_next(s, d);
        long long len = 1LL << d;
        S p = pow_prod(s, d);
        for (int e = d - 1; e >= 0; --e) {
            if (S nextp = op(p, pow_prod(cur, e)); f(nextp)) {
                swap(p, nextp);
                cur = pow_next(cur, e);
                len += 1LL << e;
            }
        }
        return len;
    }
};
using S = long long;
S op(S l, S r) { return l + r; }

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    vector<int> g(n); // 图结构
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
        // 从 i 到 (i+a[i]) % n 连边
    	g[i] = (i + a[i]) % n;
    }
    BiLiftring<S, op> b(g, a);
    for (int i = 0; i < n; ++i)
    	cout << i + 1 + b.get(i, k) << '\n';
   
    return 0;
}