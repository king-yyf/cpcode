#include <bits/stdc++.h> 
using namespace std; 

int main() { 
    int t; 
    cin >> t; 
    while (t--) { 
        int n; 
        cin >> n; 
        vector<int> b(n); 
        for (int i = 0; i < n; i++) { 
            cin >> b[i]; 
        } 

        int sum = b[0] + b[1] + b[2] - 2 ; 
        vector<int> p{b[0],b[1],b[2]};
        sort(p.rbegin(), p.rend());
        int mx1 = b[0], mx2 = b[1], mx3 = b[2]; 
        int ans = sum; 

        int l = 0, r=2;

        for (int i = 3; i < n; i++) { 
            sum += b[i]; 
            if (b[i] >= mx1) { 
                mx3 = mx2; 
                mx2 = mx1; 
                mx1 = b[i]; 
            } else if (b[i] >= mx2) { 
                mx3 = mx2; 
                mx2 = b[i]; 
            } else if (b[i] >= mx3) { 
                mx3 = b[i]; 
            } 
            int cur_ans = sum - (i - 2) * mx1 - (i - 3) * mx2 - (i - 4) * mx3; 
            ans = max(ans, cur_ans); 
        } 

        cout << ans << endl; 
    } 
    return 0; 
}