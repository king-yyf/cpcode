#include<bits/stdc++.h>
using namespace std;

long long countValidSeq(string &s) {
	int n = s.size();
	vector<int> pos(n + 1);
	stack<int> sk;
	for (int i = 1; i <= n; ++i) {
		if (s[i - 1] == '(') sk.push(i);
		else {
			if(sk.size()) {
				pos[i] = sk.top();
				sk.pop();
			}
		} 
	}
	long long ans = 0;
	vector<long long> dp(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (pos[i]) {
			dp[i] = dp[pos[i] - 1] + 1;
			ans += dp[i];
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	cout << fixed << setprecision(10);
	string s;
	while(cin>>s){
		cout << countValidSeq(s) << "\n";
	}
}