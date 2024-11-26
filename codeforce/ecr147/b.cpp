#include <bits/stdc++.h>
using namespace std;

const int MAX = 200001;

int a[MAX], a1[MAX];

int main() {
    int t, n, l, r, x, p; cin >> t;
    while (t--) {
        cin >> n;
        l = 0; r = n - 1; p = 0;
        int mi = MAX, ma = 1;
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) {
            cin >> a1[i];
            if (a[i] == a1[i] && p == 0) l = i + 1;
            else if (a[i] != a1[i] && p == 0) p = 1;
            //if (x != a[i]) p = 1, r = i;
        }
        p = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] == a1[i] && p == 0) r = i - 1;
            else if (a[i] != a1[i] && p == 0) p = 1;
            else break;
        }
        //cout << l+1 << " " << r+1 << "\n";
        for (int i = l; i <= r; ++i) {
            if (a[i] < mi) mi = a[i];
            if (a[i] > ma) ma = a[i];
        }
        while (a1[l-1] <= mi && l > 0) mi = a1[l-1], l--;
        while (a1[r+1] >= ma && r < n - 1) ma = a1[r+1], r++;
        cout << l+1 << " " << r+1 << "\n";
    }
    return 0;
}