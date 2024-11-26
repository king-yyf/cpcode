
// 最小字母CH是'a'，字母集大小K是26
template<char CH = 'a', int K = 26>
struct trie {
    struct node {
        array<int, K> child;
        int cnt[2]{0, 0};
        node () { memset(&child[0], -1, K * sizeof(int));}
    };

    vector<node> tr = {node()};

    trie(int tot_len = -1) {
        if (tot_len >= 0) tr.reserve(tot_len + 1);
    }

    int add(const string &s) {
        int p = 0; 
        for (char ch: s) {
            int u = ch - CH;
            if (tr[p].child[u] < 0) {
                tr[p].child[u] = int(tr.size());
                tr.emplace_back();
            }
            p = tr[p].child[u];
            tr[p].cnt[0]++;
        }
        tr[p].cnt[1]++;
        return p;
    }

    int get(const string &s, bool prefix_of_s = 0, bool count_prefix = 0) {
        int p = 0, ans = 0;
        for (char ch: s) {
            if (count_prefix) ans += tr[p].cnt0;
            p = tr[p].child[ch - CH];
            if (p < 0) break;
        }
        if (p >= 0) ans += tr[p].cnt[prefix_of_s];
        return ans;
    }
};


class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& a) {
        int tot=0;
        for(auto&x:a) tot+=x.size();
        trie t(tot);
        int n = a.size();
        vector<int> c(n);
        for(auto&x:a) t.add(x);
        for(int i=0;i<n;++i){
            c[i]+=t.get(a[i],0,1);
        }
        return c;
    }
};
