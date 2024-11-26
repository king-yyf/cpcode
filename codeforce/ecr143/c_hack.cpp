#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;cin >> n;
    vector<long long>a(n + 2), b(n + 2), ans(n + 2), mod(n + 2), cop(n + 2);
    for(int i = 1; i <= n;i++)cin >> a[i];
    for(int i = 1; i <= n;i++)cin >> b[i];
    cop = b;
    for(int i = 1; i <= n;i++)b[i] += b[i - 1];
    for(int i = 1; i <= n;i++){
        int idx = i - 1, l = i , r = n , mid = 0;
        while(l <= r){
            mid = (l + r) / 2;
            long long cnt = b[mid] - b[i - 1];
            if(a[i] >= cnt){
                idx = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        if(idx != i - 1){
            ans[i] += 1;
            ans[idx + 1] -= 1;
            mod[idx + 1] += (a[i] - (b[idx] - b[i - 1]));
        }
        else mod[i] += a[i];
    }
    for(int i = 1; i <= n;i++)ans[i] += ans[i - 1];
    for(int i = 1; i <= n;i++){
        ans[i] = (ans[i] * cop[i]) + mod[i];
    }
    for(int i = 1; i <= n;i++)cout << ans[i] << ' ';
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
    #endif
    int t = 1;cin >> t;
    for(int i = 1; i <= t;i++){
        solve();
    }
    return 0;
}