#include <bits/stdc++.h>
using namespace std;

// https://yukicoder.me/problems/no/2242

/*


準備として、{0,1,⋯,N} から {0,1,⋯,N} への写像（関数）G を次のように定めます。

G(k) の意味として、番号 k 以下の任意の町に行くことができるなら、そこから 1 回以内の移動で G(k) 以下の任意の町に行くことができます。なぜなら、番号 
k 以下の町 j から行くことができる町は標高が Tj 以下の任意の町であるので、j=1,2,⋯,k について考えると 
1 回以内の移動で標高が 
max{T1,T2,⋯,Tk} 以下の町に行くことができ、さらに H は単調増加であるからです。また、番号 k 以下の町はすでに行くことができているので、番号 k 以下の任意の町に行けるなら、そこから 1 回以内のの移動で番号 
G(k) 以下の任意の町に行くことができます。


*/

void wt(vector<int> &a) {
    for (int x : a)
        cout << x << ' ';
    cout << '\n';
}

using ll = long long;

// 预处理 O(NlogN)；查询：O(logN)
struct BiLifting {
    int N, INVALID, lgD;
    vector<vector<int>> mat;
    BiLifting() : N(0), lgD(0) {}
    BiLifting(const vector<int> &vec_nxt, int INVALID = -1, int lgd = 0)
        : N(vec_nxt.size()), INVALID(INVALID), lgD(lgd) {
        while ((1LL << lgD) < N) lgD++;
        mat.assign(lgD, vector<int>(N, INVALID));
        mat[0] = vec_nxt;
        for (int i = 0; i < N; i++)
            if (mat[0][i] < 0 or mat[0][i] >= N) mat[0][i] = INVALID;
        for (int d = 0; d < lgD - 1; d++) {
            for (int i = 0; i < N; i++)
                if (mat[d][i] != INVALID) mat[d + 1][i] = mat[d][mat[d][i]];
        }
    }
    int kth_next(int now, long long k) {
        if (k >= (1LL << lgD)) exit(8);
        for (int d = 0; k and now != INVALID; d++, k >>= 1)
            if (k & 1) now = mat[d][now];
        return now;
    }

    // Distance from l to [r, infty)
    // Requirement: mat[0][i] > i for all i (monotone increasing)
    int distance(int l, int r) {
        if (l >= r) return 0;
        int ret = 0;
        for (int d = lgD - 1; d >= 0; d--) {
            if (mat[d][l] < r and mat[d][l] != INVALID) ret += 1 << d, l = mat[d][l];
        }
        if (mat[0][l] == INVALID or mat[0][l] >= r)
            return ret + 1;
        else
            return -1; // Unable to reach
    }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> X(n);
    for (int &x : X)
        cin >> x;

    int L, Q;
    cin >> L >> Q;
    vector<int> r(n);
    for (int i = 0, j = 0; i < n; ++i) {
        while (j < n - 1 && X[j + 1] <= X[i] + L) j++;
        r[i] = j;    
    }

    BiLifting d(r);

    for (int i = 0; i < Q; ++i) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (x > y) swap(x, y);
        cout << d.distance(x, y) << '\n';
    }
    
    return 0;
}
