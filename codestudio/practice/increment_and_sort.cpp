#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a) {
	for (int x : a) 
		cout << x << ' ';
	cout << '\n';
}

// https://www.codingninjas.com/studio/contests/weekend-contest-89/9333824/problems/27166?leftPanelTab=0


int minimumNumberOfOperation(int n, string &s) {
	const int inf = 1e9;
    vector<int> f(n + 1, inf), g(n + 1, inf);
    f[0] = 0;
    if (s[0] == '0') f[1] = 0;
    for (int i = 1; i < n; ++i) {
    	if (s[i] == '1') {
            if (s[i - 1] == '1') {
                f[i + 1] = min(f[i + 1], f[i - 1] + 1);
                f[i] = min(f[i], f[i - 1] + 1);
            } else {
                f[i + 1] = min(f[i + 1], f[i - 1] + 3);
                f[i] = min(f[i], f[i - 1] + 3);
            }
    	}else {
            f[i + 1] = min(f[i + 1], f[i]);
            if (s[i - 1] == '1') {
                f[i + 1] = min(f[i + 1], f[i - 1] + 2);
                f[i] = min(f[i], f[i - 1] + 2);
            } else {
                f[i + 1] = min(f[i + 1], f[i - 1]);
                f[i] = min(f[i], f[i - 1]);
            }
    	}
    }
    g[n] = 0;

    if (s[n - 1] == '1') g[n - 1] = 0;
    for (int i = n - 2; i >= 0; --i) {
    	if (s[i] == '1') {
            g[i] = min(g[i], g[i + 1]);
            if (s[i + 1] == '1') {
                g[i] = min(g[i], g[i + 2]);
                g[i + 1] = min(g[i + 1], g[i + 2]);
            } else {
                g[i] = min(g[i], g[i + 2] + 1);
                g[i + 1] = min(g[i + 1], g[i + 2] + 1);
            }
    	}else {
    		if (s[i + 1] == '1') {
                g[i] = min(g[i], g[i + 2] + 2);
                g[i + 1] = min(g[i + 1], g[i + 2] + 2);
            } else {
                g[i] = min(g[i], g[i + 2] + 3);
                g[i + 1] = min(g[i + 1], g[i + 2] + 3);
            }
    	}
    }

    // wt(f);
    // wt(g);

    int ans = min(f[n], g[0]);

    for (int i = 1; i < n; ++i) {
    	ans = min(ans, f[i - 1] + g[i + 1]);
    }

    return ans;
}

int minimumNumberOfOperation1(int n, string &s) {

    int s1Count = 0, s0Count = 0, answer = n + 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            s1Count++;
        }
    }

    int oneCount = 0;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
 
        if (s[i] == '0') {

            s1Count--;
            if (oneCount == 1) {
                oneCount = 0;
                s0Count += 2;
            }
        }
        else {

            oneCount++;
            if (oneCount == 2) {
                s0Count++;
                oneCount = 0;
            }
        }

        // Update 'answer' with new calculated answer.
        ans[i] = s0Count+s1Count;
        answer = min(answer, s0Count + s1Count);
    }
    wt(ans);

    return answer;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	int n;
    	string s;
    	cin >> n >> s;

        // minimumNumberOfOperation1(n,s);

    	cout << minimumNumberOfOperation(n, s) << '\n';
    }

    return 0;
}
