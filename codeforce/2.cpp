#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T, typename less>
struct mulset_cmp {
    bool operator () (const pair<T, size_t>& x, const pair<T, size_t>& y) const {
        return less()(x.first, y.first) ? true : (less()(y.first, x.first) ? false : less()(x.second, y.second));
    }
};
 
template<typename T, typename less>
struct mulset {
    tree<pair<T, size_t>, null_type, mulset_cmp<T, less>, rb_tree_tag, tree_order_statistics_node_update> t;
    map<T, size_t> mp;

    void insert(T v) {
        t.insert({v, ++mp[v]});
    }

    void erase(T v) {
        t.erase({v, mp[v]--});
    }

    size_t order_of_key(T v) {
        return t.order_of_key({v, 0});
    }

    T find_by_order(size_t r) {
        return t.find_by_order(r)->first;
    }

    T prev(T v) {
        auto it = t.lower_bound({v, 0});
        return (--it)->first;
    }

    T next(T v) {
        return t.lower_bound({v + 1, 0})->first;
    }
};

mulset<long long, less<long long>> st;

