/**
 * Created by 5cm/s on 2023/08/28 15:43:03.
 * 诸天神佛，佑我上分！
 **/
#include <bits/stdc++.h>

using namespace std;

#define itr(it) begin(it), end(it)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
#define endl '\n'
#define YES() void(cout << "Yes\n")
#define NO() void(cout << "No\n")

template<typename T>
T chmax(T &a, T b) { return a > b ? a : (a = b); }

template<typename T>
T chmin(T &a, T b) { return a < b ? a : (a = b); }


const int N = 1e6;
vector<int> pri;
int fac[N + 1], pre[N + 1];

auto __init__ = []() -> int {
    for (int i = 2; i <= N; ++i) {
        if (!fac[i]) pri.emplace_back(i), fac[i] = i, pre[i] = 1;
        for (auto p: pri) {
            if (p * i > N) break;
            fac[p * i] = p, pre[p * i] = i;
            if (fac[i] == p) break;
        }
    }
    return 0;
}();

int bsz, cnt[N + 1], L = 1, R = 0, val = 0;

struct query {
    int l, r, id;

    bool operator<(const query &q) const {
        return l / bsz != q.l / bsz
               ? l < q.l
               : l / bsz % 2 ? r > q.r : r < q.r;
    }
};

void Add(int x, int d = 1) {
    while (x > 1) {
        int p = fac[x];
        while (fac[x] == p) {
            val += cnt[p] == 0;
            cnt[p] += d;
            if (cnt[p] >= 3) cnt[p] -= 3;
            val -= cnt[p] == 0;
            x = pre[x];
        }
    }
}

void Del(int x) {
    Add(x, 2);
}

void elysia() {
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    for (int &x: nums) {
        cin >> x;
        int y = 1;
        while (x > 1) {
            int p = fac[x], cc = 0;
            while (p == fac[x])
                cc++, x = pre[x];
            cc %= 3;
            while (cc--) y *= p;
        }
        x = y;
    }
    bsz = sqrt(n + 0.5);
    vector<query> qs(q);
    for (int i = 0; i < q; ++i) {
        auto &[l, r, id] = qs[i];
        cin >> l >> r, --l, --r, id = i;
    }
    sort(itr(qs));
    vector<int> ans(q);
    for (auto &[l, r, id]: qs) {
        while (L > l) Add(nums[--L]);
        while (R < r) Add(nums[++R]);
        while (L < l) Del(nums[L++]);
        while (R > r) Del(nums[R--]);
        ans[id] = val;
    }
    for (int v: ans)
        v == 0 ? YES() : NO();
}

int main() {
#ifdef MEGURINE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    clock_t start = clock();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T = 1;
//    cin >> T;
    cout << fixed << setprecision(12);
    while (T--) {
        elysia();
    }
    cout.flush();
#ifdef MEGURINE
    clock_t end = clock();
    cout << "\n\nRunning Time : " << (double) (end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
#endif
    return 0;
}