#include <bits/stdc++.h>
#ifdef OY_LOCAL
#include <windows.h>
// split to make windows.h before psapi.h
#include <psapi.h>
#endif
#define all(a) std::begin(a), std::end(a)
#define rall(a) std::rbegin(a), std::rend(a)
template <typename _Tp, typename _Fp, typename _Compare = std::less<void>>
bool chmax(_Tp &a, const _Fp &b, _Compare __comp = _Compare()) { return __comp(a, b) ? a = b, true : false; }
template <typename _Tp, typename _Fp, typename _Compare = std::less<void>>
bool chmin(_Tp &a, const _Fp &b, _Compare __comp = _Compare()) { return __comp(b, a) ? a = b, true : false; }
#define YESNO(condition) \
    if (condition)       \
        cout << "YES\n"; \
    else                 \
        cout << "NO\n";
using std::cin, std::cout, std::endl;
auto tam = [] {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef OY_LOCAL
#define CHECKTIME tam.stop()
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    struct TIME_AND_MEMORY {
        static auto GetMicroSecond() {
            static FILETIME ft;
            GetSystemTimeAsFileTime(&ft);
            return ft.dwLowDateTime;
        };
        static auto GetMemory() {
            PROCESS_MEMORY_COUNTERS pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
            return pmc.WorkingSetSize;
        }
        uint32_t t0, t1;
        TIME_AND_MEMORY() : t0(GetMicroSecond()) {}
        void stop() {
            t1 = GetMicroSecond();
            cout << "\ntime cost = " << (t1 - t0) / 10000.0 << " ms\nmemory cost = " << (GetMemory() >> 20) << " MB\n ";
            t0 = t1;
        }
        ~TIME_AND_MEMORY() { stop(); }
    };
    return TIME_AND_MEMORY();
#else
#define CHECKTIME
    return 0;
#endif
}();

int main() {
    int n;
    cin >> n;
    std::map<int, int> mp;
    int sum = 0;
    for (int len = 1; len <= 2000; len++) {
        sum += len;
        mp[sum] = len;
    }

    while (n--) {
        int m, s;
        cin >> m >> s;
        std::vector<int> b(m);
        for (int i = 0; i < m; i++) cin >> b[i];
        int s0 = std::accumulate(all(b), 0);
        if (!mp.count(s0 + s)) {
            cout << "NO\n";
            continue;
        }
        if (std::set<int>(all(b)).size() != m) {
            cout << "NO\n";
            continue;
        }
        int len = mp[s0 + s];
        if (*std::min_element(all(b)) < 1) {
            cout << "NO\n";
            continue;
        }
        if (*std::max_element(all(b)) > len) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
}