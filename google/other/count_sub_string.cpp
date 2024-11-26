#include<bits/stdc++.h>
using namespace std;

long long countSumString(string &s) {
    long long ans = 0, x =  0, y = 1;
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i] != s[i - 1]) {
            ans += min(x, y);
            x = y;
            y = 1;
        }else y++;
    }
    ans += min(x, y);
    return ans;
}

int main() {
	string s;
	cin>>s;
	cout<<countSumString(s)<<"\n";
}