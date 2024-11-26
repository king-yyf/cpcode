#include <bits/stdc++.h>
using namespace std;

void manacher(string s){
    int n = s.size();
    vector<int> d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) l = i - k - 1, r = i + k;
    }
}
// auto is_palindrome = [&](int l, int r) { // check s[l..(r-1)]
//     if ((r - l) % 2 == 0) return d2[(l + r) / 2] >= (r - l) / 2;
//     return d1[(l + r) / 2] >= (r - l + 1) / 2;
// }; 

template<typename T, int ALPHABET_SIZE = 26, char CH = 'a'>
struct palindrome_tree {
    // node that represents a palindromic substring
    struct node_t {
        T len, pos, cnt; // 回文子串长度、首次出现位置、出现次数
        T depth, suff;   // suff: node-index of largest palindromic suffix
        T next[ALPHABET_SIZE]; // "A".next['x'] --> "xAx"
    };

    vector<char> _str;    // string of letter ordinals (e.g. 'a' is 0)
    vector<node_t> _nodes;
    T _suff;             // node-index of the current longest palindromic suffix
    long long _total;    // 回文子串总数，可到n*n级别

    palindrome_tree() {_init();}

    palindrome_tree(string &s) {
        _init();
        add_all(s);
    }

    void _init() {
        _str.clear();  _nodes.resize(3);
        _nodes[1].len = -1, _nodes[1].suff = 1;
        _nodes[2].len = 0, _nodes[2].suff = 1;
        _suff = 2, _total = 0;
    }

    template<typename C>
    void reserve_more(C& c, size_t sz) {
        if (c.size() + sz <= c.capacity()) return;
        c.reserve(std::max(c.size() + sz, c.capacity() + c.capacity() / 2));
    }

    T add_all(string &s) {
        size_t len = s.size();
        reserve_more(_str, len), reserve_more(_nodes, len);
        T c = 0;
        for (auto &ch: s) c += add(ch);
        return c;
    }

    T add(char let) {
        let = let - CH;
        _str.push_back(let);
        T i = _find_suffix(_suff, let);
        _suff = _nodes[i].next[let];
        if (_suff != 0) {
            _nodes[_suff].cnt++, _total += _nodes[_suff].depth;
            return 0;
        }
        T suff2 = _find_suffix2(i, let);
        _suff = (T)_nodes.size();
        _nodes.push_back({});
        _nodes[_suff].len = _nodes[i].len + 2;
        _nodes[_suff].pos = (T)_str.size() - _nodes[_suff].len;
        _nodes[_suff].cnt = 1;
        _nodes[_suff].suff = suff2;
        _nodes[_suff].depth = _nodes[suff2].depth + 1;
        _nodes[i].next[let] = _suff;
        _total += _nodes[_suff].depth;
        return 1;
    }

    T _find_suffix2(T i, char let) {
        if (i == 1) return 2;
        i = _find_suffix(_nodes[i].suff, let);
        return _nodes[i].next[let];
    }

    T _find_suffix(T i, char let) {
        T sz = (T)_str.size();
        while (sz < _nodes[i].len + 2 || _str[sz - _nodes[i].len - 2] != let) {
            i = _nodes[i].suff;
        }
        return i;
    }

    // This should be called only once after all elements are added!
    void propagate() {
        for (T i = (T)_nodes.size() - 1; i >= 3; i--) {
            T suff = _nodes[i].suff;
            _nodes[suff].cnt += _nodes[i].cnt;
        }
    }

    // Returns the number of total palindromic substrings, counting their multiplicities.
    long long total() const { return _total;}

    // Returns the number of distinct palindromic substrings, each counted only once.
    T distinct() const { return (T)_nodes.size() - 3;}

    // Returns the index of the node representing the longest palindromic suffix.
    T longest_suffix() const { return _suff;}

    // Returns the <length, index> of longest Palindrome substrings
    array<T, 2> longest_palindrome() const {
        T longest = 0, index = 0;
        for (int i = 3; i < (T)_nodes.size(); ++i) 
            if (_nodes[i].len > longest) 
                longest = _nodes[i].len, index = _nodes[i].pos;
        return {longest, index};
        
    } 

    // Returns the number of nodes.
    T size() const { return (T)_nodes.size();}

    // Accesses node by its index.
    node_t& operator[] (T index) { return _nodes[index];}
};
void solve() {
	int n; 
	string s, t;
	cin >> n >> s >> t;

	vector<int> s1(n), s2(n), t1(n), t2(n);

	manacher(s, s1, s2);
	manacher(t, t1, t2);

	int c = 0;
	for (int i = 0; i < n; ++i) {
		c = max({c, 2 * s1[i] - 1, 2 * t1[i] - 1, 2 * s2[i], 2 * t2[i]});
		c = max({c, s1[i] + 1 + })
	}

	cout << c << "\n";
}

int main(){
	ios::sync_with_stdio(0); 
	cin.tie(0);

	solve();

	return 0;
}
