
template<typename T>
struct fenwick_tree {
    static int highest_bit(unsigned x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }
 
    int tree_n = 0;
    T tree_sum = T();
    vector<T> tree;
 
    fenwick_tree(int n = -1) {
        if (n >= 0)
            init(n);
    }
 
    void init(int n) {
        tree_n = n;
        tree_sum = T();
        tree.assign(tree_n + 1, T());
    }
 
    // O(n) initialization of the Fenwick tree.
    template<typename T_array>
    void build(const T_array &initial) {
        assert(int(initial.size()) == tree_n);
        tree_sum = T();
 
        for (int i = 1; i <= tree_n; i++) {
            tree[i] = initial[i - 1];
            tree_sum += initial[i - 1];
 
            for (int k = (i & -i) >> 1; k > 0; k >>= 1)
                tree[i] += tree[i - k];
        }
    }
 
    // index is in [0, tree_n).
    void update(int index, const T &change) {
        assert(0 <= index && index < tree_n);
        tree_sum += change;
 
        for (int i = index + 1; i <= tree_n; i += i & -i)
            tree[i] += change;
    }
 
    // Returns the sum of the range [0, count).
    T query(int count) const {
        count = min(count, tree_n);
        T sum = T();
 
        for (int i = count; i > 0; i -= i & -i)
            sum += tree[i];
 
        return sum;
    }
 
    // Returns the sum of the range [start, tree_n).
    T query_suffix(int start) const {
        return tree_sum - query(start);
    }
 
    // Returns the sum of the range [a, b).
    T query(int a, int b) const {
        return query(b) - query(a);
    }
 
    // Returns the element at index a in O(1) amortized across every index. Equivalent to query(a, a + 1).
    T get(int a) const {
        assert(0 <= a && a < tree_n);
        int above = a + 1;
        T sum = tree[above];
        above -= above & -above;
 
        while (a != above) {
            sum -= tree[a];
            a -= a & -a;
        }
 
        return sum;
    }
 
    bool set(int index, T value) {
        assert(0 <= index && index < tree_n);
        T current = get(index);
 
        if (current == value)
            return false;
 
        update(index, value - current);
        return true;
    }
 
    // Returns the largest p in `[0, tree_n]` such that `query(p) <= sum`. Returns -1 if no such p exists (`sum < 0`).
    // Can be used as an ordered set/multiset on indices in `[0, tree_n)` by using the tree as a 0/1 or frequency array:
    // `set(index, 1)` is equivalent to insert(index). `update(index, +1)` is equivalent to multiset.insert(index).
    // `set(index, 0)` or `update(index, -1)` are equivalent to erase(index).
    // `get(index)` provides whether index is present or not, or the count of index (if multiset).
    // `query(index)` provides the count of elements < index.
    // `find_last_prefix(k)` finds the k-th smallest element (0-indexed). Returns `tree_n` for `sum >= set.size()`.
    int find_last_prefix(T sum) const {
        if (sum < T())
            return -1;
 
        int prefix = 0;
 
        for (int k = highest_bit(tree_n); k >= 0; k--)
            if (prefix + (1 << k) <= tree_n && tree[prefix + (1 << k)] <= sum) {
                prefix += 1 << k;
                sum -= tree[prefix];
            }
 
        return prefix;
    }
};


//Codeforces Global Round 18, problem: (D) X(or)-mas Tree,
struct bipartite_union_find {
    vector<int> parent;
    vector<int> size;
    vector<bool> bipartite;
    vector<bool> edge_parity;
    int components = 0;
 
    bipartite_union_find(int n = -1) {
        if (n >= 0)
            init(n);
    }
 
    void init(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        bipartite.assign(n + 1, true);
        edge_parity.assign(n + 1, false);
        components = n;
 
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
 
    int find(int x) {
        if (x == parent[x])
            return x;
 
        int root = find(parent[x]);
        edge_parity[x] = edge_parity[x] ^ edge_parity[parent[x]];
        return parent[x] = root;
    }
 
    // Returns true if x and y are in the same component.
    bool query_component(int x, int y) {
        return find(x) == find(y);
    }
 
    // Returns the parity status between x and y (0 = same, 1 = different). Requires them to be in the same component.
    bool query_parity(int x, int y) {
        assert(query_component(x, y));
        return edge_parity[x] ^ edge_parity[y];
    }
 
    // Returns {union succeeded, edge consistent with bipartite conditions}.
    pair<bool, bool> unite(int x, int y, bool different = true) {
        int x_root = find(x);
        int y_root = find(y);
 
        if (x_root == y_root) {
            bool consistent = !(edge_parity[x] ^ edge_parity[y] ^ different);
 
            if (!consistent)
                bipartite[x_root] = false;
 
            return {false, consistent};
        }
 
        bool needed_parity = edge_parity[x] ^ edge_parity[y] ^ different;
        x = x_root;
        y = y_root;
 
        if (size[x] < size[y])
            swap(x, y);
 
        parent[y] = x;
        size[x] += size[y];
        bipartite[x] = bipartite[x] && bipartite[y];
        edge_parity[y] = needed_parity;
        components--;
        return {true, true};
    }
 
    // Add an assertion that x and y are different; i.e., a normal edge.
    pair<bool, bool> add_different_edge(int x, int y) {
        return unite(x, y, true);
    }
 
    // Add an assertion that x and y are the same.
    pair<bool, bool> add_same_edge(int x, int y) {
        return unite(x, y, false);
    }
};


//Codeforces Global Round 18, problem: (E) Purple Crayon
using T_tree = int64_t;
const T_tree T_INF = numeric_limits<T_tree>::max() / 2;
 
struct segment_change {
    T_tree to_add;
 
    segment_change(T_tree _to_add = 0) : to_add(_to_add) {}
 
    bool has_change() const {
        return to_add != 0;
    }
 
    // Return the combined result of applying this segment_change followed by `other`.
    segment_change combine(const segment_change &other) const {
        return segment_change(to_add + other.to_add);
    }
};
 
struct segment {
    T_tree maximum;
    int index;
 
    segment(T_tree _maximum = -T_INF, int _index = -1) : maximum(_maximum), index(_index) {}
 
    void apply(int, const segment_change &change) {
        maximum += change.to_add;
    }
 
    void join(const segment &other) {
        if (other.maximum > maximum) {
            maximum = other.maximum;
            index = other.index;
        }
    }
 
    void join(const segment &a, const segment &b) {
        *this = a;
        join(b);
    }
};
 
pair<int, int> right_half[32];
 
struct add_max_seg_tree {
    static int highest_bit(unsigned x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }
 
    int tree_n = 0;
    vector<segment> tree;
    vector<segment_change> changes;
 
    add_max_seg_tree(int n = -1) {
        if (n >= 0)
            init(n);
    }
 
    void init(int n) {
        tree_n = 1;
 
        while (tree_n < n)
            tree_n *= 2;
 
        tree.assign(2 * tree_n, segment());
        changes.assign(tree_n, segment_change());
    }
 
    // Builds our tree from an array in O(n).
    void build(const vector<segment> &initial) {
        int n = int(initial.size());
        init(n);
        assert(n <= tree_n);
 
        for (int i = 0; i < n; i++)
            tree[tree_n + i] = initial[i];
 
        for (int position = tree_n - 1; position > 0; position--)
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
    }
 
    void apply_and_combine(int position, int length, const segment_change &change) {
        tree[position].apply(length, change);
 
        if (position < tree_n)
            changes[position] = changes[position].combine(change);
    }
 
    void push_down(int position, int length) {
        if (changes[position].has_change()) {
            apply_and_combine(2 * position, length / 2, changes[position]);
            apply_and_combine(2 * position + 1, length / 2, changes[position]);
            changes[position] = segment_change();
        }
    }
 
    // Calls push_down for all necessary nodes in order to query the range [a, b).
    void push_all(int a, int b) {
        assert(0 <= a && a < b && b <= tree_n);
        a += tree_n;
        b += tree_n - 1;
 
        for (int up = highest_bit(tree_n); up > 0; up--) {
            int x = a >> up, y = b >> up;
            push_down(x, 1 << up);
            if (x != y) push_down(y, 1 << up);
        }
    }
 
    void join_and_apply(int position, int length) {
        tree[position].join(tree[2 * position], tree[2 * position + 1]);
        tree[position].apply(length, changes[position]);
    }
 
    // Calls join for all necessary nodes after updating the range [a, b).
    void join_all(int a, int b) {
        assert(0 <= a && a < b && b <= tree_n);
        a += tree_n;
        b += tree_n - 1;
        int length = 1;
 
        while (a > 1) {
            a /= 2;
            b /= 2;
            length *= 2;
            join_and_apply(a, length);
            if (a != b) join_and_apply(b, length);
        }
    }
 
    template<typename T_range_op>
    void process_range(int a, int b, bool needs_join, T_range_op &&range_op) {
        if (a == b) return;
        push_all(a, b);
        int original_a = a, original_b = b;
        int length = 1, r_size = 0;
 
        for (a += tree_n, b += tree_n; a < b; a /= 2, b /= 2, length *= 2) {
            if (a & 1)
                range_op(a++, length);
 
            if (b & 1)
                right_half[r_size++] = {--b, length};
        }
 
        for (int i = r_size - 1; i >= 0; i--)
            range_op(right_half[i].first, right_half[i].second);
 
        if (needs_join)
            join_all(original_a, original_b);
    }
 
    segment query(int a, int b) {
        assert(0 <= a && a <= b && b <= tree_n);
        segment answer;
 
        process_range(a, b, false, [&](int position, int) {
            answer.join(tree[position]);
        });
 
        return answer;
    }
 
    segment query_full() const {
        return tree[1];
    }
 
    void update(int a, int b, const segment_change &change) {
        assert(0 <= a && a <= b && b <= tree_n);
 
        process_range(a, b, true, [&](int position, int length) {
            apply_and_combine(position, length, change);
        });
    }
 
    void set_value(int index, T_tree value) {
        assert(0 <= index && index < tree_n);
        T_tree current = query(index, index + 1).maximum;
        update(index, index + 1, segment_change(value - current));
    }
 
    void maximize(int index, T_tree value) {
        assert(0 <= index && index < tree_n);
        T_tree current = query(index, index + 1).maximum;
 
        if (value > current)
            update(index, index + 1, segment_change(value - current));
    }
 
    vector<segment> to_array() {
        for (int i = 1; i < tree_n; i++)
            push_down(i, tree_n >> highest_bit(i));
 
        vector<segment> segs(tree_n);
 
        for (int i = 0; i < tree_n; i++)
            segs[i] = tree[tree_n + i];
 
        return segs;
    }
};

//Codeforces LATOKEN Round 1 (Div. 1 + Div. 2), problem: (F1) Falling Sand 
struct SCC {
    int V = 0;
    vector<vector<int>> adj;
    vector<int> tour_index, low_link;
    int tour;
 
    vector<int> stack;
    vector<bool> in_stack;
 
    vector<vector<int>> components;
    vector<int> which_component;
 
    SCC(int v = 0) {
        init(v);
    }
 
    SCC(const vector<vector<int>> &_adj) {
        init(_adj);
    }
 
    void init(int v) {
        V = v;
        adj.assign(V, {});
    }
 
    void init(const vector<vector<int>> &_adj) {
        adj = _adj;
        V = int(adj.size());
    }
 
    void add_edge(int a, int b) {
        adj[a].push_back(b);
    }
 
    // Tarjan's algorithm.
    void dfs(int node) {
        tour_index[node] = tour++;
        low_link[node] = tour_index[node];
        stack.push_back(node);
        in_stack[node] = true;
 
        for (int neighbor : adj[node])
            if (tour_index[neighbor] < 0) {
                // neighbor is part of our subtree.
                dfs(neighbor);
                low_link[node] = min(low_link[node], low_link[neighbor]);
            } else if (in_stack[neighbor]) {
                // neighbor is a candidate for low_link.
                low_link[node] = min(low_link[node], tour_index[neighbor]);
            }
 
        if (low_link[node] == tour_index[node]) {
            // node is the highest node in an SCC, which includes everything on the stack up to it.
            components.emplace_back();
            vector<int> &component = components.back();
            int x;
 
            do {
                assert(!stack.empty());
                x = stack.back();
                stack.pop_back();
                in_stack[x] = false;
                which_component[x] = int(components.size()) - 1;
                component.push_back(x);
            } while (x != node);
        }
    }
 
    void build() {
        tour_index.assign(V, -1);
        low_link.resize(V);
        which_component.assign(V, -1);
 
        stack.clear();
        stack.reserve(V);
        in_stack.assign(V, false);
        tour = 0;
 
        // Note that Tarjan's algorithm provides the SCCs in reverse topological order.
        components = {};
 
        for (int i = 0; i < V; i++)
            if (tour_index[i] < 0)
                dfs(i);
    }
};

//Codeforces LATOKEN Round 1 (Div. 1 + Div. 2), problem: (G) A New Beginning
// Note: make sure T can handle sums of values, not just individual values.
template<typename T>
struct convex_piecewise_linear {
    priority_queue<T> negative;
    priority_queue<T, vector<T>, greater<T>> positive;
    T neg_offset = 0, pos_offset = 0, minimum = 0;
 
    T get_min() const {
        return minimum;
    }
 
    // Equivalent to dp[x] = min(dp[x], ..., dp[x + shift]).
    void expand_negative(T shift) {
        neg_offset -= shift;
    }
 
    // Equivalent to dp[x] = min(dp[x - shift], ..., dp[x]).
    void expand_positive(T shift) {
        pos_offset += shift;
    }
 
    // Equivalent to dp[x] = min(dp[x - shift], ..., dp[x + shift]).
    void expand_both(T shift) {
        expand_negative(shift);
        expand_positive(shift);
    }
 
    // Equivalent to dp[x] += max(a - x, 0).
    void add_negative(T a) {
        if (positive.empty() || a <= positive.top() + pos_offset) {
            negative.push(a - neg_offset);
            return;
        }
 
        T pos_start = positive.top() + pos_offset;
        minimum += a - pos_start;
        negative.push(pos_start - neg_offset);
        positive.pop();
        positive.push(a - pos_offset);
    };
 
    // Equivalent to dp[x] += max(x - a, 0).
    void add_positive(T a) {
        if (negative.empty() || a >= negative.top() + neg_offset) {
            positive.push(a - pos_offset);
            return;
        }
 
        T neg_start = negative.top() + neg_offset;
        minimum += neg_start - a;
        positive.push(neg_start - pos_offset);
        negative.pop();
        negative.push(a - neg_offset);
    };
 
    // Equivalent to dp[x] += abs(x - a).
    void add_abs(T a) {
        add_negative(a);
        add_positive(a);
    }
};


template<typename T, bool maximum_mode = false>
struct online_RMQ {
    static int highest_bit(int x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }
 
    int n = 0, levels = 0;
    vector<T> values;
    vector<vector<int>> range_low;
 
    online_RMQ(const vector<T> &_values = {}) {
        for (T value : _values)
            add(value);
    }
 
    // Note: when `values[a] == values[b]`, returns b.
    int better_index(int a, int b) const {
        return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;
    }
 
    void add(T value) {
        n++;
 
        if (highest_bit(n) + 1 > levels) {
            levels = highest_bit(n) + 1;
            range_low.emplace_back();
        }
 
        values.push_back(value);
        range_low[0].push_back(n - 1);
 
        for (int k = 1; k < levels; k++) {
            int index = int(range_low[k].size());
            range_low[k].push_back(better_index(range_low[k - 1][index], range_low[k - 1][index + (1 << (k - 1))]));
        }
    }
 
    // Note: breaks ties by choosing the largest index.
    int query_index(int a, int b) const {
        assert(0 <= a && a < b && b <= n);
        int level = highest_bit(b - a);
        return better_index(range_low[level][a], range_low[level][b - (1 << level)]);
    }
 
    T query_value(int a, int b) const {
        return values[query_index(a, b)];
    }
};


//Codeforces Round #692 (Div. 1, based on Technocup 2021 Elimination Round 3), problem: (E) No Game No Life
// Warning: this only handles the case where # equations >= # variables and there is a valid solution.
template<typename float_t>
struct gaussian {
    int n;
    vector<vector<float_t>> coefficients;
    vector<float_t> values;
 
    gaussian(int _n = 0) {
        init(_n);
    }
 
    void init(int _n) {
        n = _n;
        coefficients = {};
        values = {};
    }
 
    void add_equation(const vector<float_t> &coefs, float_t value) {
        assert(int(coefs.size()) == n);
        coefficients.push_back(coefs);
        values.push_back(value);
    }
 
    void swap_rows(int a, int b) {
        swap(coefficients[a], coefficients[b]);
        swap(values[a], values[b]);
    }
 
    // Eliminates `coefficients[target][col]` by canceling the `target` row with the `source` row.
    void eliminate(int target, int source, int col, int start_col = 0) {
        if (coefficients[target][col] == 0)
            return;
 
        assert(coefficients[source][col] != 0);
        float_t ratio = coefficients[target][col] / coefficients[source][col];
 
        for (int i = start_col; i < n; i++)
            coefficients[target][i] -= coefficients[source][i] * ratio;
 
        coefficients[target][col] = 0;
        values[target] -= values[source] * ratio;
    }
 
    vector<float_t> solve() {
        int rows = int(coefficients.size());
        assert(rows >= n);
 
        for (int i = 0; i < n; i++) {
            int largest = i;
 
            for (int row = i + 1; row < rows; row++)
                if (coefficients[row][i] > coefficients[largest][i])
                    largest = row;
 
            swap_rows(largest, i);
 
            for (int row = i + 1; row < rows; row++)
                eliminate(row, i, i, i);
        }
 
        vector<float_t> answers(n, 0);
 
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++)
                assert(coefficients[i][j] == 0);
 
            float_t value = values[i];
 
            for (int j = i + 1; j < n; j++)
                value -= coefficients[i][j] * answers[j];
 
            answers[i] = value / coefficients[i][i];
        }
 
        return answers;
    }
};


//Codeforces Global Round 12, problem: (E) Capitalism,
struct check_bipartite {
    int V;
    vector<vector<int>> adj;
    vector<int> depth;
    vector<bool> visited;
 
    check_bipartite(int v = -1) {
        if (v >= 0)
            init(v);
    }
 
    void init(int v) {
        V = v;
        adj.assign(V, {});
    }
 
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    vector<array<vector<int>, 2>> components;
 
    bool dfs(int node, int parent) {
        assert(!visited[node]);
        visited[node] = true;
        depth[node] = parent < 0 ? 0 : depth[parent] + 1;
        components.back()[depth[node] % 2].push_back(node);
 
        for (int neigh : adj[node])
            if (neigh != parent) {
                if (!visited[neigh] && !dfs(neigh, node))
                    return false;
 
                if (depth[node] % 2 == depth[neigh] % 2)
                    return false;
            }
 
        return true;
    }
 
    // Returns true iff the graph is bipartite.
    // Also builds a vector of components, where each component is divided into its two parts.
    bool solve() {
        depth.assign(V, -1);
        visited.assign(V, false);
        components = {};
 
        for (int i = 0; i < V; i++)
            if (!visited[i]) {
                components.emplace_back();
 
                if (!dfs(i, -1))
                    return false;
            }
 
        return true;
    }
};



//Codeforces Round #681 (Div. 1, based on VK Cup 2019-2020 - Final), problem: (C) Graph Transposition

const int64_t TIEBREAK = int64_t(1e9) + 5;
const int LOG = 20;
const int64_t INF64 = int64_t(2e18) + 5;
 
struct Dijkstra {
    struct state {
        int64_t dist;
        int node;
        int trans;
 
        state() {}
 
        state(int64_t _dist, int _node, int _trans) : dist(_dist), node(_node), trans(_trans) {}
 
        bool operator<(const state &other) const {
            return dist > other.dist;
        }
    };
 
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> rev_adj;
    vector<int64_t> dist[LOG + 2];
 
    Dijkstra(int _n = 0) {
        init(_n);
    }
 
    void init(int _n) {
        n = _n;
        adj.assign(n, {});
        rev_adj.assign(n, {});
    }
 
    void add_directional_edge(int a, int b) {
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }
 
    void dijkstra_check(priority_queue<state> &pq, int node, int trans, int64_t new_dist) {
        if (new_dist < dist[trans][node]) {
            dist[trans][node] = new_dist;
            pq.emplace(new_dist, node, trans);
        }
    }
 
    void dijkstra(const vector<int> &source) {
        for (int t = 0; t <= LOG + 1; t++)
            dist[t].assign(n, INF64);
 
        priority_queue<state> pq;
 
        for (int src : source)
            dijkstra_check(pq, src, 0, 0);
 
        auto increment = [&](int trans) {
            return trans <= LOG ? trans + 1 : LOG;
        };
 
        while (!pq.empty()) {
            state top = pq.top();
            pq.pop();
 
            if (top.dist > dist[top.trans][top.node])
                continue;
 
            const vector<int> &forward = top.trans % 2 == 0 ? adj[top.node] : rev_adj[top.node];
            const vector<int> &backward = top.trans % 2 == 0 ? rev_adj[top.node] : adj[top.node];
 
            for (int neigh : forward)
                dijkstra_check(pq, neigh, top.trans, top.dist + 1);
 
            for (int neigh : backward)
                dijkstra_check(pq, neigh, increment(top.trans), top.dist + 1 + (top.trans >= LOG ? TIEBREAK : 0));
        }
    }
};


//Codeforces Round #680 (Div. 1, based on Moscow Team Olympiad), problem: (C) Team-Building,
struct union_find {
    // When data[x] < 0, x is a root and -data[x] is its tree size. When data[x] >= 0, data[x] is x's parent.
    vector<int> data;
    int components = 0;
 
    union_find(int n = -1) {
        if (n >= 0)
            init(n);
    }
 
    void init(int n) {
        data.assign(n + 1, -1);
        components = n;
    }
 
    int find(int x) {
        return data[x] < 0 ? x : data[x] = find(data[x]);
    }
 
    int get_size(int x) {
        return -data[find(x)];
    }
 
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
 
        if (x == y)
            return false;
 
        if (-data[x] < -data[y])
            swap(x, y);
 
        data[x] += data[y];
        data[y] = x;
        components--;
        return true;
    }
};
 
struct check_bipartite {
    int V;
    vector<vector<int>> adj;
    vector<int> depth;
    vector<bool> visited;
 
    check_bipartite(int v = -1) {
        if (v >= 0)
            init(v);
    }
 
    void init(int v) {
        V = v;
        adj.assign(V, {});
    }
 
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    vector<array<vector<int>, 2>> components;
 
    bool dfs(int node, int parent) {
        assert(!visited[node]);
        visited[node] = true;
        depth[node] = parent < 0 ? 0 : depth[parent] + 1;
        components.back()[depth[node] % 2].push_back(node);
 
        for (int neigh : adj[node])
            if (neigh != parent) {
                if (!visited[neigh] && !dfs(neigh, node))
                    return false;
 
                if (depth[node] % 2 == depth[neigh] % 2)
                    return false;
            }
 
        return true;
    }
 
    // Returns true iff the graph is bipartite.
    // Also builds a vector of components, where each component is divided into its two parts.
    bool solve() {
        depth.assign(V, -1);
        visited.assign(V, false);
        components = {};
 
        for (int i = 0; i < V; i++)
            if (!visited[i]) {
                components.emplace_back();
 
                if (!dfs(i, -1))
                    return false;
            }
 
        return true;
    }
};
 
struct bipartite_union_find {
    vector<int> parent;
    vector<int> size;
    vector<bool> bipartite;
    vector<bool> edge_parity;
    int components = 0;
 
    bipartite_union_find(int n = -1) {
        if (n >= 0)
            init(n);
    }
 
    void init(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        bipartite.assign(n + 1, true);
        edge_parity.assign(n + 1, false);
        components = n;
 
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
 
    int find(int x) {
        if (x == parent[x])
            return x;
 
        int root = find(parent[x]);
        edge_parity[x] = edge_parity[x] ^ edge_parity[parent[x]];
        return parent[x] = root;
    }
 
    // Returns true if x and y are in the same component.
    bool query_component(int x, int y) {
        return find(x) == find(y);
    }
 
    // Returns the parity status between x and y. Requires that they are in the same component.
    bool query_parity(int x, int y) {
        int x_root = find(x);
        int y_root = find(y);
        assert(x_root == y_root);
        return edge_parity[x] ^ edge_parity[y];
    }
 
    // Returns {union succeeded, edge consistent with bipartite conditions}.
    pair<bool, bool> unite(int x, int y, bool different = true) {
        int x_root = find(x);
        int y_root = find(y);
 
        if (x_root == y_root) {
            bool consistent = !(edge_parity[x] ^ edge_parity[y] ^ different);
 
            if (!consistent)
                bipartite[x_root] = false;
 
            return {false, consistent};
        }
 
        bool needed_parity = edge_parity[x] ^ edge_parity[y] ^ different;
        x = x_root;
        y = y_root;
 
        if (size[x] < size[y])
            swap(x, y);
 
        parent[y] = x;
        size[x] += size[y];
        bipartite[x] = bipartite[x] && bipartite[y];
        edge_parity[y] = needed_parity;
        components--;
        return {true, true};
    }
 
    // Add an assertion that x and y are different; i.e., a normal edge.
    pair<bool, bool> add_different_edge(int x, int y) {
        return unite(x, y, true);
    }
 
    // Add an assertion that x and y are the same.
    pair<bool, bool> add_same_edge(int x, int y) {
        return unite(x, y, false);
    }
};


//Codeforces Round #679 (Div. 1, based on Technocup 2021 Elimination Round 1), problem: (A) P
struct segment {
    int64_t maximum;
 
    segment(int64_t _maximum = numeric_limits<int64_t>::lowest()) : maximum(_maximum) {}
 
    void join(const segment &other) {
        maximum = max(maximum, other.maximum);
    }
 
    void join(const segment &a, const segment &b) {
        *this = a;
        join(b);
    }
};
 
int right_half[32];
 
struct basic_seg_tree {
    static const bool POWER_OF_TWO_MODE = true;
 
    int tree_n = 0;
    vector<segment> tree;
 
    basic_seg_tree(int n = -1) {
        if (n >= 0)
            init(n);
    }
 
    void init(int n) {
        if (POWER_OF_TWO_MODE) {
            tree_n = 1;
 
            while (tree_n < n)
                tree_n *= 2;
        } else {
            tree_n = n;
        }
 
        tree.assign(2 * tree_n, segment());
    }
 
    // Builds our tree from an array in O(n).
    void build(const vector<segment> &initial) {
        int n = int(initial.size());
        init(n);
        assert(n <= tree_n);
 
        for (int i = 0; i < n; i++)
            tree[tree_n + i] = initial[i];
 
        for (int position = tree_n - 1; position > 0; position--)
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
    }
 
    segment query(int a, int b) const {
        assert(0 <= a && a <= b && b <= tree_n);
        segment answer;
        int r_size = 0;
 
        for (a += tree_n, b += tree_n; a < b; a /= 2, b /= 2) {
            if (a & 1)
                answer.join(tree[a++]);
 
            if (b & 1)
                right_half[r_size++] = --b;
        }
 
        for (int i = r_size - 1; i >= 0; i--)
            answer.join(tree[right_half[i]]);
 
        return answer;
    }
 
    segment query_single(int index) const {
        assert(0 <= index && index < tree_n);
        return tree[tree_n + index];
    }
 
    void join_up(int position) {
        while (position > 1) {
            position /= 2;
            tree[position].join(tree[2 * position], tree[2 * position + 1]);
        }
    }
 
    void update(int index, const segment &seg) {
        assert(0 <= index && index < tree_n);
        int position = tree_n + index;
        tree[position] = seg;
        join_up(position);
    }
 
    template<typename T_bool>
    int find_last_prefix(int n, T_bool &&should_join) const;
 
    template<typename T_bool>
    int find_last_subarray(int n, int start, T_bool &&should_join) const;
};

