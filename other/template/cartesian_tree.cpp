#include <bits/stdc++.h>
using namespace std;



using C_Type = vector<array<int, 2>>;
struct CartesianTree : public  C_Type{
    static constexpr int absent = -1;
    const int root;
    CartesianTree() : C_Type(), root(0) {}
    CartesianTree(int root, const C_Type& g) : C_Type(g), root(root) {}
    CartesianTree(int root, C_Type&& g) : C_Type(move(g)), root(root) {}
    auto ranges() const {
        vector<pair<int, int>> res;
        res.reserve(size());
        auto dfs = [&](auto dfs, int l, int m, int r) -> void {
            if (m == absent) return;
            const auto& [lm, rm] = (*this)[m];
            dfs(dfs, l, lm, m), res.emplace_back(l, r), dfs(dfs, m + 1, rm, r);
        };
        dfs(dfs, 0, root, size());
        return res;
    }
};
template <typename Comp>
struct CartesianTreeBuilder {
    CartesianTreeBuilder() = default;
    template <typename RAC>
    CartesianTreeBuilder(const RAC& a, Comp comp = Comp{}) : n(a.size()), comp(comp), par(calc_par(a, comp)) {}

    CartesianTree build() const {
        int root = -1;
        C_Type g(n, { CartesianTree::absent, CartesianTree::absent });
        for (int i = 0; i < n; ++i) {
            int p = par[i];
            (p >= 0 ? g[p][p <= i] : root) = i;
        }
        return CartesianTree{ root, move(g) };
    }
    template <typename RAC>
    static CartesianTree build(const RAC& a, Comp comp = Comp{}) {
        return CartesianTreeBuilder(a, comp).build();
    }
    int parent(int i) const { assert(i < n); return par[i];}
    int operator[](int i) const { return parent(i);}
private:
    const int n;
    const Comp comp;
    const vector<int> par;
    template <typename RAC>
    static vector<int> calc_par(const RAC& a, Comp comp) {
        const int n = a.size();
        vector<int> par(n, -1);
        for (int i = 1; i < n; ++i) {
            int p = i - 1, l = i;
            while (p >= 0 and comp(a[i], a[p])) l = p, p = par[p];
            par[l] = i, par[i] = p;
        }
        return par;
    }
};
using MinCartesianTreeBuilder = CartesianTreeBuilder<less<>>;
using MaxCartesianTreeBuilder = CartesianTreeBuilder<greater<>>;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    return 0;
}

