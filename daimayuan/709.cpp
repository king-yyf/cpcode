#include<bits/stdc++.h>
using namespace std;

long long maxWeightSum(vector<int> &a) {
    int n = a.size();
    vector<vector<long long>> dp(n, vector<long long>(2));
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[i - 1]) {
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + a[i] - a[i - 1]);
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        } else {
            dp[i][0] = max(dp[i - 1][0] + a[i - 1] - a[i], dp[i - 1][1]);
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]);
        }
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}

bool next_balanced_sequence(string &s) {
    int n = s.size(), dep = 0;
    for (int i = n - 1; i >= 0; --i) {
        dep += (s[i] == '(') ? -1 : 1;
        if (s[i] == '(' && dep > 0) {
            dep--;
            int l = (n - i - 1 - dep) / 2, r = n - i - 1 - l;
            string t = s.substr(0, i) + ')' + string(l, '(') + string(r, ')');
            s.swap(t);
            return true;
        }
    }
    return false;
}

using T = long long; //mint
T rank_of_sequence(string &s) {
    int n = s.size();
    vector dp(n + 1, vector<T>(n + 1));
    dp[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i - 1][1];
        for (int j = 1; j < n; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
        }
    }
    int idx = 0;
    T ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] == ')') ans += dp[n - i][idx + 1], idx--;
        else idx++;
    }
    return ans + 1;
}

int f[40][40];
inline void pre(int n){
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        f[i][0]=f[i-1][1];
        for(int j=1;j<=n;j++) f[i][j]=f[i-1][j-1]+f[i-1][j+1];
    }
}
inline T rank11(string &s){
    int n=s.size();
    pre(n);
    T ans = 0;
    int num=0;
    for(int i=1;i<=n;i++){
        if(s[i-1]==')') ans+=f[n-i][num+1],num--;
        else num++;
    }
    return ans+1;
}

string kth_balanced(int n, T k) {
    vector d(2 * n + 1,vector<T>(n + 1));
    d[0][0] = 1;
    for (int i = 1; i <= 2 * n; ++i) {
        d[i][0] = d[i - 1][1];
        for (int j = 1; j < n; ++j) 
            d[i][j] = d[i-1][j-1] + d[i-1][j+1];
        d[i][n] = d[i-1][n-1];
    }
    string ans;
    int dep = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (dep + 1 <= n && d[2 * n - i - 1][dep + 1] >= k) {
            ans += '(';
            dep++;
        } else {
            ans += ')';
            if (dep + 1 <= n) k -= d[2 * n - i - 1][dep + 1];
            dep--;
        }
    }
    return ans;
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	// cout << maxWeightSum(a) << "\n";

    string s = "((()))()";
    n = s.size() / 2;
    for (int i = 0; i < 3; ++i) {
        cout << s << "\n";
        T x1 = rank11(s), x2 = rank_of_sequence(s);
        cout << x1 << ", " << x2 << "\n";
        cout << kth_balanced(n, x1) << "\n";
        next_balanced_sequence(s);
    }
	return 0;
}