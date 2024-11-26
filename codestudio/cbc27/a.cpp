#include <bits/stdc++.h>
using namespace std;

int minimumDifferenceCount(int n, vector<int> &nums) {
    int p_max = 1;
    for(int a : nums) p_max = max(p_max, a >> (__builtin_ctz(a)));
    vector<int> upper;
    int min = p_max;
    for(int a : nums){
        if(a & 1) a <<= 1;
        if(a >= p_max){
            a >>= __builtin_clz(p_max) - __builtin_clz(a);
            if(a < p_max) a <<= 1;
            upper.push_back(a);
        }
        min = std::min(min, a);
    }
    sort(upper.begin(), upper.end());
    int ans = upper.back() - min;
    for(int i = upper.size() - 1; upper[i] > p_max; i -= 1){
        min = std::min(min, upper[i] >> 1);
        ans = std::min(ans, upper[i - 1] - min);
    }
    return ans;
}


void ac_yyf(int tt) {
    
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
