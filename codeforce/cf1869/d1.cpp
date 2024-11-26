#include <iostream> 
#include <vector> 
 
using namespace std; 
 
int main() { 
    int t; 
    cin >> t; 
 
    while (t--) { 
        int n; 
        cin >> n; 
 
        vector<long long> a(n); 
        for (int i = 0; i < n; i++) { 
            cin >> a[i]; 
        } 
 
        long long sum = 0; 
        for (int i = 0; i < n; i++) { 
            sum += a[i]; 
        } 
 
        if (sum % n != 0) { 
            cout << "No" << endl; 
            continue; 
        } 
 
        long long target = sum / n; 
        bool possible = true; 
        long long excess = 0; 
 
        for (int i = 0; i < n; i++) {
            if (a[i] > target) { 
                long long diff = a[i] - target; 
                if (i < n - 1) { 
                    a[i] -= diff; 
                    a[i + 1] += diff; 
                } else { 
                    excess += diff; 
                } 
            } else if (a[i] < target) { 
                long long diff = target - a[i]; 
                if (i < n - 1) { 
                    a[i] += diff; 
                    a[i + 1] -= diff; 
                } else { 
                    excess -= diff; 
                } 
            } 
 
            if (excess != 0) { 
                possible = false; 
                break; 
            } 
        } 
 
        if (possible) { 
            cout << "Yes" << endl; 
        } else { 
            cout << "No" << endl; 
        } 
    } 
 
    return 0; 
}