#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
    for(auto&x:a)cout<<x<<' ';cout<<'\n';
}

template<typename T>
struct ST {
    int n = 0;
    vector<vector<T>> mat;
    static int largest_bit(int x) { return 31 - __builtin_clz(x);}
    ST(const vector<T> &a = {}) { if (!a.empty()) build(a);}
    void build(const vector<T> &a) {
        n = int(a.size());
        int max_log = largest_bit(n) + 1;
        mat.resize(max_log);
        for (int k = 0; k < max_log; k++)
            mat[k].resize(n - (1 << k) + 1);
        if (n > 0) mat[0] = a;

        for (int k = 1; k < max_log; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                mat[k][i] = min(mat[k - 1][i], mat[k - 1][i + (1 << (k - 1))]);
    }
    T get_val(int a, int b) const {
        assert(0 <= a && a < b && b <= n);
        int t = largest_bit(b - a);
        return min(mat[t][a], mat[t][b - (1 << t)]);
    }
};
template <class T = int, bool build_lcp = false> 
struct SA {
    int n = -1;
    vector<int> sa, rnk, lcp, s2;
    ST<int> st;
    SA(): n(0) {}
    SA(const vector<T>& s) : n(s.size()), s2(n) {
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
        int now = 0;
        for (int i = 0; i < n; ++i) {
            if (i && s[idx[i - 1]] != s[idx[i]]) now++;
            s2[idx[i]] = now;
        }
        get_suffix_array(s2, now);
        if (build_lcp) lcp_array(s2);
    }
    SA(const string& s) : n(s.size()), s2(n){
        for (int i = 0; i < n; ++i) s2[i] = s[i];
        get_suffix_array(s2, 255);
        if (build_lcp) lcp_array(s2);
    }
    void get_suffix_array(vector<int>& s, int upper) {
        assert(0 <= upper);
        for (int d : s) assert(0 <= d && d <= upper);
        sa = sa_is(s, upper);
    }
    vector<int> sa_naive(const vector<int>& s) {
        int n = int(s.size());
        vector<int> sa(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int l, int r) {
            if (l == r) return false;
            while (l < n && r < n) {
                if (s[l] != s[r]) return s[l] < s[r];
                l++, r++;
            }
            return l == n;
        });
        return sa;
    }
    vector<int> sa_doubling(const vector<int>& s) {
        int n = int(s.size());
        vector<int> sa(n), rnk = s, tmp(n);
        iota(sa.begin(), sa.end(), 0);
        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int x, int y) {
                if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
                int rx = x + k < n ? rnk[x + k] : -1, ry = y + k < n ? rnk[y + k] : -1;
                return rx < ry;
            };
            sort(sa.begin(), sa.end(), cmp);
            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++) 
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            swap(tmp, rnk);
        }
        return sa;
    }

    template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
    vector<int> sa_is(const vector<int>& s, int upper) {
        int n = int(s.size());
        if (n == 0) return {}; if (n == 1) return {0};
        if (n == 2) { if (s[0] < s[1]) return {0, 1}; else return {1, 0};}
        if (n < THRESHOLD_NAIVE) return sa_naive(s);
        if (n < THRESHOLD_DOUBLING) return sa_doubling(s);
        vector<int> sa(n), sum_l(upper + 1), sum_s(upper + 1);
        vector<bool> ls(n);
        for (int i = n - 2; i >= 0; i--) 
            ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
        for (int i = 0; i < n; i++) {
            if (!ls[i]) sum_s[s[i]]++;
            else sum_l[s[i] + 1]++;
        }
        for (int i = 0; i <= upper; i++) {
            sum_s[i] += sum_l[i];
            if (i < upper) sum_l[i + 1] += sum_s[i];
        }

        auto induce = [&](const vector<int>& lms) {
            fill(sa.begin(), sa.end(), -1);
            vector<int> buf(upper + 1);
            copy(sum_s.begin(), sum_s.end(), buf.begin());
            for (auto d : lms) {
                if (d == n) continue;
                sa[buf[s[d]]++] = d;
            }
            copy(sum_l.begin(), sum_l.end(), buf.begin());
            sa[buf[s[n - 1]]++] = n - 1;
            for (int i = 0; i < n; i++) {
                int v = sa[i];
                if (v >= 1 && !ls[v - 1]) sa[buf[s[v - 1]]++] = v - 1;
            }
            copy(sum_l.begin(), sum_l.end(), buf.begin());
            for (int i = n - 1; i >= 0; i--) {
                int v = sa[i];
                if (v >= 1 && ls[v - 1]) sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        };

        vector<int> lms_map(n + 1, -1), lms;
        int m = 0;
        for (int i = 1; i < n; i++) {
            if (!ls[i - 1] && ls[i])  lms_map[i] = m++;
        }
        lms.reserve(m);
        for (int i = 1; i < n; i++) if (!ls[i - 1] && ls[i]) lms.push_back(i);
        induce(lms);
        if (m) {
            vector<int> sorted_lms, rec_s(m);
            sorted_lms.reserve(m);
            for (int v : sa) 
                 if (lms_map[v] != -1) sorted_lms.push_back(v);
            int rec_upper = 0;
            rec_s[lms_map[sorted_lms[0]]] = 0;
            for (int i = 1; i < m; i++) {
                int l = sorted_lms[i - 1], r = sorted_lms[i];
                int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
                int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
                bool same = true;
                if (end_l - l != end_r - r) same = false;
                else {
                    while (l < end_l) {
                        if (s[l] != s[r]) break;
                        l++, r++;
                    }
                    if (l == n || s[l] != s[r]) same = false;
                }
                if (!same) rec_upper++;
                rec_s[lms_map[sorted_lms[i]]] = rec_upper;
            }

            auto rec_sa = sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

            for (int i = 0; i < m; i++) 
                sorted_lms[i] = lms[rec_sa[i]];
            induce(sorted_lms);
        }
        return sa;
    }
    void get_rnk() {rnk.resize(n); for(int i = 0; i < n; ++i) rnk[sa[i]] = i;}
    void lcp_array(vector<T>& s) {
        assert(n >= 1);
        get_rnk();
        lcp.assign(n - 1, 0);
        int h = 0;
        for (int i = 0; i < n; ++i) {
            if (h > 0) h--;
            if (rnk[i] == 0) continue;
            int j = sa[rnk[i] - 1];
            for (; j + h < n && i + h < n; h++) 
                if (s[j + h] != s[i + h]) break;
            lcp[rnk[i] - 1] = h;
        }
    }
    bool contains(const string& s) { // 是否包含子串s O(mlog(n))
        int m = s.size();
        auto cmp = [&](int x) {
            for (int j = 0; x + j < n and j < m; ++j) {
                if (s2[x + j] < s[j]) return -1;
                if (s2[x + j] > s[j]) return 1;
            }
            return n - x < m ? -1 : 0; 
        };
        int l = 0, r = n - 1;
        while (l <= r) {
            int md = (l + r) / 2;
            int c = cmp(sa[md]);
            if (c == 0) return true;
            else if (c < 0)  l = md + 1;
            else r = md - 1;
        }
        return false;
    }
    int count(const string& s) { // s作为子串的出现次数 O(mlog(n))
        int m = s.size();
        if (n < m) return 0;
        auto lower = [&](int h) {
            for (int j = 0; h + j < n and j < m; j++) {
                if (s2[h + j] < s[j]) return true;
                if (s2[h + j] > s[j]) return false;
            }
            return n - h < m;
        };
        auto upper = [&](int h) {
            for (int j = 0; h + j < n and j < m; j++) 
                if (s2[h + j] > s[j]) return false;
            return true;
        };
        const auto L = partition_point(sa.begin(), sa.end(), lower);
        const auto R = partition_point(L, sa.end(), upper);
        return distance(L, R);
        // return vector<int>(L, R); // 如果需要返回出现的位置
    }
    long long distinct_substr() const { // 不同子串的数目, assert(build_lcp = True)
        long long res = n * (n + 1ll) / 2;
        for (int x : lcp) 
            res -= x;
        return res;
    }
    //返回s,t的最长公共子串<s中的下标，长度>，传入 s+'#'+t，m为s.size()
    pair<int, int> longest_common_substr(int m) { // assert(build_lcp = True)
        int len = 0, idx = 0;
        for (int i = 0; i < n - 1; ++i) {
            if ((sa[i] < m) != (sa[i + 1] < m) && lcp[i] > len) 
                len = lcp[i], idx = sa[i];
        }
        return {idx, len};
    }
    void build_rmq() {vector<int> a(n);for(int i=1; i<n; ++i) a[i]=lcp[i-1]; st.build(a);} 
    int get_lcp_from_ranks(int a, int b) const { //保证build_rmq已执行
        if (a == b) return n - sa[a];
        if (a > b) swap(a, b);
        return st.get_val(a + 1, b + 1);
    }
    int get_lcp(int a, int b) const { //s[a:n-1],s[b:n-1]的最长公共前缀
        if (a >= n || b >= n) return 0;
        if (a == b) return n - a;
        return get_lcp_from_ranks(rnk[a], rnk[b]);
    }
    int comp(int a, int b, int len = -1) const { //O(1)时间比较s[a:a+len-1],s[b:b+len-1]
        if (len < 0) len = n; if (a == b) return 0;
        int k = get_lcp(a, b); if (k >= len) return 0;
        if (a + k >= n || b + k >= n) return a + k >= n ? -1 : 1;
        return s2[a + k] < s2[b + k] ? -1 : (s2[a + k] == s2[b + k] ? 0 : 1);
    }
    void sort_substrs(vector<array<int, 2>> &qs) { // a[i]: s[l..r-1]
        sort(qs.begin(), qs.end(), [&](array<int, 2> &a, array<int, 2> &b){
            int n1 = a[1] - a[0], n2 = b[1] - b[0], cmp = comp(a[0], b[0], min(n1, n2));
            if (cmp != 0) return cmp < 0;
            return n1 != n2 ? n1 < n2 : (a < b);
        });
    }
    long long count_borders() const { // assert(build_lcp = True)
        long long ans = (n + 1ll) * n / 2, s = 0;
        vector<pair<int,int>> sk;
        for (int i = 1; i < n; ++i) {
            int len = lcp[i - 1], cnt = 1;
            while (!sk.empty() && len <= sk.back().first) {
                s -= sk.back().first * 1ll * sk.back().second;
                cnt += sk.back().second;
                sk.pop_back();
            }
            sk.emplace_back(len, cnt);
            s += len * 1ll * cnt;
            ans += s;
        }
        return ans;
    }
};

int longest_common_subarr(int n, vector<vector<int>> &qs) {
    int tot = 0, m = qs.size(), l = 0, r = 1e9, sum = 0, ans = 0;
    for (auto &v : qs) { sum += v.size();}
    vector<int> pos(sum + m - 1), a(sum + m - 1);
    for (int i = 0; i < m; ++i) {
        int t = qs[i].size();
        if (t < r) r = t;
        for (int j = 0; j < t; ++j) {
            pos[tot] = i;
            a[tot++] = qs[i][j];
        }
        if (i + 1 < m) a[tot++] = n + i;
    }
    SA<int, 1> sa(a);
    while (l <= r) {
        int md = (l + r) / 2, ok = 0;
        vector<int> vis(m);
        for (int i = 1; i < tot; ++i) {
            if (sa.lcp[i - 1] >= md) {
                int j = i, cnt = 0;
                for (; j < tot && sa.lcp[j - 1] >= md; j++);
                for (int k = i - 1; k < j; ++k) if (!vis[pos[sa.sa[k]]]++)
                    cnt++;
                for (int k = i - 1; k < j; ++k) 
                    vis[pos[sa.sa[k]]]--;
                i = j - 1;
                if (cnt >= m) {ok = 1; break;}
            }
        }
        if (ok) {ans = md; l = md + 1;} 
        else r = md - 1;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<vector<int>> qs = {
        {0,1,2,3,4},
        {2,3,4},
        {4,0,1,2,3}
    };
    auto p=longest_common_subarr(5,qs);
    return 0;
}
