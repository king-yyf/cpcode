#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-2216

void wt(vector<int> &a){
    for(int x:a)cout<<x<<' ';cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), p(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
        p[a[i]] = i;
    }

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        ans += i == 0 || (p[i] < p[i - 1]);
    }

    wt(a);
    wt(p);
    swap(a[1], a[3]);

    for (int i = 0; i < n; ++i) {
        p[a[i]] = i;
    }

     wt(a);
    wt(p);



    cout << ans << '\n';

    return 0;
}
