#include <bits/stdc++.h>
using namespace std;
// https://codeforces.com/contest/1430/problem/E
using ll = long long;

template<class Fun> class y_combinator_result {
    Fun _f;
public:
    template<class T> explicit y_combinator_result(T &&fun): _f(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return _f(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_comb(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }
template<typename T, typename F> //i < j,且f(a[i], a[j])为true的数对数目
long long count_pairs(T a, F &&f) {
	T buff(a.size());
	return y_comb([&](auto self, int start, int end) -> long long {
        if (end - start <= 1) return 0;
        int mid = (start + end) / 2, left = start, right = mid, n = 0;
        long long res = self(start, mid) + self(mid, end);
        while (left < mid || right < end)
            if (left < mid && (right == end || f(a[left], a[right]))) {
                buff[n++] = a[left++];
            } else {
                buff[n++] = a[right++], res += left - start;
            }
        copy(buff.begin(), buff.begin() + n, a.begin() + start);
        return res;
    })(0, int(a.size()));
}
 // 顺序对: count_pairs(a, less<int>()); // less_equal<int>()
 // 逆序对: count_pairs(a, greater<int>()); // greater_equal<int>()

long long swapCount(string &s, string &t) {
	int n = s.size();
	map<int,vector<int>> mp;
	for (int i = 0; i < n; ++i) {
		mp[t[i]].push_back(i);
	}
	vector<int> a(n);
	for (int i = n - 1; i >= 0; --i) {
		a[i] = mp[s[i]].back();
		mp[s[i]].pop_back();
	}
	return count_pairs(a,greater<int>());
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    string s;
    cin>>n>>s;
    auto t=s;
    reverse(t.begin(), t.end());
    cout<<swapCount(t,s)<<"\n";

    return 0;
}
