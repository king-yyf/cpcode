#include<bits/stdc++.h>
using namespace std;
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

    // prefix_of_s=1: trie中多少个字符串等于 s (如果count_prefix=1，求多少个字符串是s的前缀)
    // prefix_of_s=0: s是trie中多少个字符串的前缀 (如果count_prefix=1，对s的每个前缀也进行累加)
    int get(const string &s, bool prefix_of_s = 0, bool count_prefix = 0) {
        int p = 0, ans = 0;
        for (char ch: s) {
            if (count_prefix) ans += tr[p].cnt[prefix_of_s];
            p = tr[p].child[ch - CH];
            if (p < 0) break;
        }
        if (p >= 0) ans += tr[p].cnt[prefix_of_s];
        return ans;
    }
};

void solve() {

	int n, q;
	cin >> n >> q;
	trie<0, 62> t;

	auto get=[&](char c) {
		if(c>='a'&&c<='z'){
			return c-'a';
		}else if(c>='A'&&c<='Z'){
			return c-'A'+26;
		}
		return c-'0' + 52;
	};
	string s;

	for (int i = 0; i < n; ++i) {
		cin >> s;
		for(auto&x:s)x=get(x);
		t.add(s);
	}
	for (int i = 0; i < q; ++i) {
		cin >> s;
		for(auto&x:s)x=get(x);
		cout << t.get(s, 0, 0)<<"\n";
	}
}

int main(){
	int t; cin >> t;
	while(t--){
		solve();
	}
}