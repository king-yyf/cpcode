#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T, int DIM> struct Ndarray {
	static_assert(DIM >= 0, "DIM must >= 0");
	array<int, DIM> shape, strides; T* data;
	Ndarray(array<int, DIM> sp, array<int, DIM> st, T* d) : shape(sp), strides(st), data(d) {}
	Ndarray() : shape{0}, strides{0}, data(nullptr) {}
	int flatten_index(array<int, DIM> idx, bool checked = false) const {
		int res = 0;
		for (int i = 0; i < DIM; i++) { 
			if (checked) assert(0 <= idx[i] && idx[i] < shape[i]);
			res += idx[i] * strides[i]; 
		}
		return res;
	}
	T& operator[] (array<int, DIM> idx) const { return data[flatten_index(idx)];}
	T& at(array<int, DIM> idx) const { return data[flatten_index(idx, true)];}
	template <int D = DIM>
	typename enable_if<(0 < D), Ndarray<T, DIM-1>>::type operator[] (int idx) const {
		array<int, DIM-1> nshape; copy(shape.begin()+1, shape.end(), nshape.begin());
		array<int, DIM-1> nstrides; copy(strides.begin()+1, strides.end(), nstrides.begin());
		T* ndata = data + (strides[0] * idx);
		return Ndarray<T, DIM-1>(nshape, nstrides, ndata);
	}
	template <int D = DIM> typename enable_if<(0 < D), Ndarray<T, DIM-1>>::type at(int x) const { 
	    assert(0 <= x && x < shape[0]); return operator[](x);
    }
	template <int D = DIM> typename enable_if<(0 == D), T&>::type operator * () const { return *data;}
};
 
template <typename T, int DIM> struct ndarr {
	static_assert(DIM >= 0, "DIM must >= 0");
	array<int, DIM> shape, strides;
	int len; T* data;
	ndarr() : shape{0}, strides{0}, len(0), data(nullptr) {}
	explicit ndarr(array<int, DIM> shape_, const T& t = T()) {
		shape = shape_, len = 1;
		for (int i = DIM-1; i >= 0; i--) { strides[i] = len; len *= shape[i];}
		data = new T[len];
		fill(data, data + len, t);
	}
	ndarr(const ndarr& o) : shape(o.shape), strides(o.strides), len(o.len), data(new T[len]) {
		for (int i = 0; i < len; i++) data[i] = o.data[i];
	}
	ndarr& operator=(ndarr&& o) noexcept {
		swap(shape, o.shape); swap(strides, o.strides);
		swap(len, o.len); swap(data, o.data);
		return *this;
	}
	ndarr(ndarr&& o) : ndarr() { *this = move(o);}
	ndarr& operator=(const ndarr& o) { return *this = ndarr(o);}
	~ndarr() { delete[] data; }
	using view_t = Ndarray<T, DIM>;
	view_t view() { return Ndarray<T, DIM>(shape, strides, data);}
	operator view_t() { return view(); }
	using const_view_t = Ndarray<const T, DIM>;
	const_view_t view() const { return Ndarray<const T, DIM>(shape, strides, data);}
	operator const_view_t() const { return view(); }
	T& operator[] (array<int, DIM> idx) { return view()[idx]; }
 
	T& at(array<int, DIM> idx) { return view().at(idx); }
	const T& operator[] (array<int, DIM> idx) const { return view()[idx]; }
	const T& at(array<int, DIM> idx) const { return view().at(idx); }
	template <int D = DIM> typename enable_if<(0 < D), Ndarray<T, DIM-1>>::type operator[] (int x) { return view()[x];}
	template <int D = DIM> typename enable_if<(0 < D), Ndarray<T, DIM-1>>::type at(int x) { return view().at(x);}
	template <int D = DIM> typename enable_if<(0 < D), Ndarray<const T, DIM-1>>::type operator[] (int x) const { return view()[x];}
	template <int D = DIM> typename enable_if<(0 < D), Ndarray<const T, DIM-1>>::type at(int x) const { return view().at(x);}
	template <int D = DIM> typename enable_if<(0 == D), T&>::type operator * () { return *view(); }
	template <int D = DIM> typename enable_if<(0 == D), const T&>::type operator * () const { return *view();}
};

using T = int;
T dp(string &s, int k) {
	int n = s.size();
	ndarr<T, 3> f({n, k, n * 2 + 1}, -1);
	function<T(int, int, int, bool, bool)> dfs = [&](int p, int v, int d, bool limit, bool is_num) -> T {
		if (p == n) return is_num && !v && d == n; // 模为0，且奇偶数位相同(偏移量n)
		if (!limit && is_num && ~f[{p, v, d}]) return f[{p, v, d}];
		T res{};
		if (!is_num) res = dfs(p + 1, v, d, false, false);
		int up = limit ? s[p] - '0' : 9;
		for (int i = 1 - is_num; i <= up; ++i) {
			res += dfs(p + 1, (v * 10 + i) % k, d + (i % 2 == 1 ? 1 : -1), limit && i == up, true);
		}
		if (!limit && is_num)
			f[{p, v, d}] = res;
		return res;
	};
	return dfs(0, 0, n, true, false);
}

class Solution {
public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
    	string r = to_string(high), l = to_string(low - 1);
    	int x = dp(r, k), y = dp(l, k);
        return x - y;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int low, high, k;
    cin >> low >> high >> k;

    Solution so;

    cout << so.numberOfBeautifulIntegers(low, high, k) << '\n';


    return 0;
}
