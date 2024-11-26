#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        if(k == 26) return 1;

        int n = s.size();
        int f[n+1], freq1[26], ne1[n+1], freq2[26], ne2[n+1], mask[n+1];
        f[n] = 0;
        memset(freq1, 0, sizeof(freq1));
        memset(freq2, 0, sizeof(freq2));
        ne1[n] = ne2[n] = n;
        mask[n] = (1 << 26) - 1;

        for(int i = n-1, cnt1 = 0, cnt2 = 0, pos1 = n-1, pos2 = n-1, curmask = mask[n]; i >= 0; --i) {
            if(++freq1[s[i] - 'a'] == 1) ++cnt1;
            if(++freq2[s[i] - 'a'] == 1) ++cnt2, curmask ^= (1 << (s[i] - 'a'));
            while(cnt1 > k)
                if(--freq1[s[pos1--] - 'a'] == 0) --cnt1;
            while(cnt2 > k-1)
                if(--freq2[s[pos2--] - 'a'] == 0) --cnt2, curmask ^= (1 << (s[pos2+1] - 'a'));
            f[i] = f[pos1+1] + 1;
            ne1[i] = pos1 + 1;
            ne2[i] = pos2 + 1;
            mask[i] = curmask;
            // 注意这里 mask[i] 额外记录了区间右侧第一个字符，作为出现过的字符
            if(pos2 + 1 < n && (mask[i] & (1 << (s[pos2 + 1] - 'a'))))
                mask[i] ^= (1 << (s[pos2 + 1] - 'a'));
        }

        int res = f[0];

        for(int start = 0, end = ne1[start], prev = 0; start < n; start = end, end = ne1[start], ++prev) {
            int mid = ne2[start];
            // 1. 改变的下标 [start, mid]
            if(max(start + k, mid) < n)
                res = max(res, prev + 1 + f[max(start + k, mid)]);
            // 2. 改变的下标 (mid, end)
            int pre = 0;
            for(int i = start; i <= min(n-1, mid); ++i) pre |= 1 << (s[i] - 'a');
            pre ^= (1 << 26) - 1;
            for(int i = mid + 1; i < end; ++i)
                if((pre & mask[i+1])) res = max(res, prev + 2 + f[ne2[i+1]]);
        }

        return res;
    }
};


int main() {
   Solution so;
    string s;
    int k;
    cin>>s>>k;
    cout<<so.maxPartitionsAfterOperations(s,k)<<"\n";
    return 0;
}
