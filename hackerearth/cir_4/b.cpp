#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
 
long long getTime(int A, int B, int C, int D, vector<int> T) {
    int n = T.size();
    vector<long long> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = T[i];
    }
    auto work = [&](int t, int cnt) {
        long long x = -1;
        priority_queue<ll, vector<ll>, greater<ll>> q;
        for (int i = 0; i < n; ++i) {
            long long c = max(p[i], x);
            while (q.size() && q.top() <= c) {
                q.pop();
                cnt++;
            }
            if (cnt) {
                cnt--;
                q.push(c + t);
                p[i] = c + t;
            } else {
                p[i] = q.top(), x = p[i];
                i--;
            }
        }
    };
    work(A, B);
    work(C, D);
    return p[n - 1];
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int A,B,C,D;
    cin >> A>>B>>C>>D;
    int n;
    cin >> n;
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        cin >> pos[i];    
    }
 
    cout << getTime(A, B, C, D, pos);
    return 0;
}
Language: C++17