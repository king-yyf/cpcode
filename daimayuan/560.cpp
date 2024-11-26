#include <bits/stdc++.h>
using namespace std;

#define int long long

long long gcd(long long a, long long b) {
    a = abs(a), b = abs(b);
    while (b != 0) {
        a %= b;
        swap (a, b);
    }
    return a;
}
long long  a, b;//给的分数
string sa, sb;//字符串形式
long long  up, down;//分数的最简
long long  del_up[10], del_down[10];
bool issub(string t, string s) {
    // mst(del_down);
    memset(del_down,0,sizeof del_down);
    int j = 0;
    for (int i = 0; i < t.length(); i++) {
        if (t[i] == s[j])j++;
        else {
            del_down[t[i] - '0']++;
        }
    }
    return j == s.length();
}
bool check(int new_down) {
    string s = to_string(new_down);
    if (!issub(sb, s))return 0;
    for (int i = 1; i < 10; i++)if (del_up[i] != del_down[i])return 0;
    if (del_up[0] == del_down[0])return 1;
    if (del_up[0] > del_down[0])return 0;
    string nsb = sb;
    int cot = del_down[0] - del_up[0];
    for (int i = 0; i < nsb.length(); i++) {
        if (nsb[i] == '0') {
            cot--;
            if (cot == 0) {
                nsb = nsb.substr(i + 1, nsb.length() - i);
                break;
            }
        }
    }
    return issub(nsb, s);
}
void slove() {
    cin >> a >> b;
    int g = gcd(a, b);
    up = a / g, down = b / g;
    sa = to_string(a), sb = to_string(b);
    int ans = a;
    for (int tar = 1; tar < (1 << sa.length()); tar++) {
        memset(del_up,0,sizeof del_up);
        string s;
        bitset<64> f(tar);//bitset来枚举二进制
        for (int i = 0; i < sa.length(); i++) {
            if (f[i])s.push_back(sa[i]);
            else del_up[sa[i] - '0']++;
        }
        int new_up = stoll(s);
        if (new_up == 0)continue;
        if (new_up % up != 0)continue;
        if (check(new_up / up * down)) {
            ans = min(ans, new_up);
        }
    }
    cout << ans << " " << ans / up * down << endl;
}

signed main(){
	slove();
}