#include <bits/stdc++.h>
using namespace std;

using ll = int;

const int mod = 1e9 + 7;

struct xor_basis {
    int b[31], nb[31], tot, siz;

    xor_basis() : tot(0) {
        siz = 0;
        memset(b, 0, sizeof(b));
        memset(nb, 0, sizeof(nb));
    }
    
    // 向线性基中插入一个数
    bool add(int x) {
        for(int i = 62; ~i; i--)
            if (x & (1LL << i)) {
                if (!b[i]) {siz++; b[i] = x; break;}
                x ^= b[i];
            }
        return x > 0;
    }

    // 判断线性基中元素能否异或得到 x
    bool check(int x) {
        for (int i = 63; ~i; --i) 
            if (x & (1LL << i)) {
                if (!b[i]) return false;
                x ^= b[i];
            }
            return 1;
    }

    //求线性空间与x异或的最大值
    int max_val(int x = 0) {
        int res = x;
        for(int i = 62; i >= 0; i--)
            res = max(res, res ^ b[i]);
        return res;
    }

    //求线性空间与x异或的最小值
    int min_val(int x) {
        int res = x;
        for(int i = 0;i <= 62; i++)
            if (b[i]) res ^= b[i];
        return res;
    }   

    //将线性基改造成每一位相互独立，即对于二进制的某一位i，只有pi的这一位是1，其它都是0
    void rebuild() {
        tot = 0;
        for(int i = 62; ~i; i--)
            for(int j = i - 1; ~j; j--)
                if (b[i] & (1LL << j)) b[i] ^= b[j];
        for(int i = 0;i <= 62; i++)
            if (b[i]) nb[tot++] = b[i];
    }

    //求线性基能够组成的数中的第K小
    int kth_min(int k) {
        if(k >= (1ll << tot)) return -1; //k大于子集总数, 找不到
        int res = 0;
        for(int i = 62; i >= 0; i--)
            if (k & (1LL << i)) res ^= nb[i];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    xor_basis b;
    for (int i = 0; i < n; ++i) {
        b.add(a[i]);
    }

    if (!b.check(0)) {
        cout << "1\n";
        return 0;
    }

    vector<int> p(n + 1);
    p[1] = 2;
    for (int i = 2; i <= n; ++i) {
        p[i] = (p[i - 1] * 2ll) % mod;
    }

    cout << p[n - b.siz] << '\n';

    return 0;
}
